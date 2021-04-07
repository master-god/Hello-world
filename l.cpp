#include <vector>
#include <cassert>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <iostream>
  #include <stdlib.h>

#define U(i,j) U_[(i)*dim[0]+(j)]
#define S(i,j) S_[(i)*dim[1]+(j)]
#define V(i,j) V_[(i)*dim[1]+(j)]

template <class T>
void GivensL(T* S_, const size_t dim[2], size_t m, T a, T b){
  T r=sqrt(a*a+b*b);
  T c=a/r;
  T s=-b/r;

  #pragma omp parallel for
  for(size_t i=0;i<dim[1];i++){
    T S0=S(m+0,i);
    T S1=S(m+1,i);
    S(m  ,i)+=S0*(c-1);
    S(m  ,i)+=S1*(-s );

    S(m+1,i)+=S0*( s );
    S(m+1,i)+=S1*(c-1);
  }
}

template <class T>
void GivensR(T* S_, const size_t dim[2], size_t m, T a, T b){
  T r=sqrt(a*a+b*b);
  T c=a/r;
  T s=-b/r;

  #pragma omp parallel for
  for(size_t i=0;i<dim[0];i++){
    T S0=S(i,m+0);
    T S1=S(i,m+1);
    S(i,m  )+=S0*(c-1);
    S(i,m  )+=S1*(-s );

    S(i,m+1)+=S0*( s );
    S(i,m+1)+=S1*(c-1);
  }
}

template <class T>
void SVD(const size_t dim[2], T* U_, T* S_, T* V_, T eps=-1){
  assert(dim[0]>=dim[1]);

  { // Bi-diagonalization
    size_t n=std::min(dim[0],dim[1]);
    std::vector<T> house_vec(std::max(dim[0],dim[1]));
    for(size_t i=0;i<n;i++){
      // Column Householder
      {
        T x1=S(i,i);
        if(x1<0) x1=-x1;

        T x_inv_norm=0;
        for(size_t j=i;j<dim[0];j++){
          x_inv_norm+=S(j,i)*S(j,i);
        }
        if(x_inv_norm>0) x_inv_norm=1/sqrt(x_inv_norm);

        T alpha=sqrt(1+x1*x_inv_norm);
        T beta=x_inv_norm/alpha;

        house_vec[i]=-alpha;
        for(size_t j=i+1;j<dim[0];j++){
          house_vec[j]=-beta*S(j,i);
        }
        if(S(i,i)<0) for(size_t j=i+1;j<dim[0];j++){
          house_vec[j]=-house_vec[j];
        }
      }
      #pragma omp parallel for
      for(size_t k=i;k<dim[1];k++){
        T dot_prod=0;
        for(size_t j=i;j<dim[0];j++){
          dot_prod+=S(j,k)*house_vec[j];
        }
        for(size_t j=i;j<dim[0];j++){
          S(j,k)-=dot_prod*house_vec[j];
        }
      }
      #pragma omp parallel for
      for(size_t k=0;k<dim[0];k++){
        T dot_prod=0;
        for(size_t j=i;j<dim[0];j++){
          dot_prod+=U(k,j)*house_vec[j];
        }
        for(size_t j=i;j<dim[0];j++){
          U(k,j)-=dot_prod*house_vec[j];
        }
      }

      // Row Householder
      if(i>=n-1) continue;
      {
        T x1=S(i,i+1);
        if(x1<0) x1=-x1;

        T x_inv_norm=0;
        for(size_t j=i+1;j<dim[1];j++){
          x_inv_norm+=S(i,j)*S(i,j);
        }
        if(x_inv_norm>0) x_inv_norm=1/sqrt(x_inv_norm);

        T alpha=sqrt(1+x1*x_inv_norm);
        T beta=x_inv_norm/alpha;

        house_vec[i+1]=-alpha;
        for(size_t j=i+2;j<dim[1];j++){
          house_vec[j]=-beta*S(i,j);
        }
        if(S(i,i+1)<0) for(size_t j=i+2;j<dim[1];j++){
          house_vec[j]=-house_vec[j];
        }
      }
      #pragma omp parallel for
      for(size_t k=i;k<dim[0];k++){
        T dot_prod=0;
        for(size_t j=i+1;j<dim[1];j++){
          dot_prod+=S(k,j)*house_vec[j];
        }
        for(size_t j=i+1;j<dim[1];j++){
          S(k,j)-=dot_prod*house_vec[j];
        }
      }
      #pragma omp parallel for
      for(size_t k=0;k<dim[1];k++){
        T dot_prod=0;
        for(size_t j=i+1;j<dim[1];j++){
          dot_prod+=V(j,k)*house_vec[j];
        }
        for(size_t j=i+1;j<dim[1];j++){
          V(j,k)-=dot_prod*house_vec[j];
        }
      }
    }
  }

  size_t k0=0;
  if(eps<0){
    eps=1.0;
    while(eps+(T)1.0>1.0) eps*=0.5;
    eps*=64.0;
  }
  while(k0<dim[1]-1){ // Diagonalization
    T S_max=0.0;
    for(size_t i=0;i<dim[1];i++) S_max=(S_max>S(i,i)?S_max:S(i,i));

    while(k0<dim[1]-1 && fabs(S(k0,k0+1))<=eps*S_max) k0++;
    if(k0==dim[1]-1) continue;

    size_t n=k0+2;
    while(n<dim[1] && fabs(S(n-1,n))>eps*S_max) n++;

    T alpha=0;
    T beta=0;
    { // Compute mu
      T C[2][2];
      C[0][0]=S(n-2,n-2)*S(n-2,n-2);
      if(n-k0>2) C[0][0]+=S(n-3,n-2)*S(n-3,n-2);
      C[0][1]=S(n-2,n-2)*S(n-2,n-1);
      C[1][0]=S(n-2,n-2)*S(n-2,n-1);
      C[1][1]=S(n-1,n-1)*S(n-1,n-1)+S(n-2,n-1)*S(n-2,n-1);

      T b=-(C[0][0]+C[1][1])/2;
      T c=  C[0][0]*C[1][1] - C[0][1]*C[1][0];
      T d=0;
      if(b*b-c>0) d=sqrt(b*b-c);
      else{
        T b=(C[0][0]-C[1][1])/2;
        T c=-C[0][1]*C[1][0];
        if(b*b-c>0) d=sqrt(b*b-c);
      }

      T lambda1=-b+d;
      T lambda2=-b-d;

      T d1=lambda1-C[1][1]; d1=(d1<0?-d1:d1);
      T d2=lambda2-C[1][1]; d2=(d2<0?-d2:d2);
      T mu=(d1<d2?lambda1:lambda2);

      alpha=S(k0,k0)*S(k0,k0)-mu;
      beta=S(k0,k0)*S(k0,k0+1);
    }

    for(size_t k=k0;k<n-1;k++)
    {
      size_t dimU[2]={dim[0],dim[0]};
      size_t dimV[2]={dim[1],dim[1]};
      GivensR(S_,dim ,k,alpha,beta);
      GivensL(V_,dimV,k,alpha,beta);

      alpha=S(k,k);
      beta=S(k+1,k);
      GivensL(S_,dim ,k,alpha,beta);
      GivensR(U_,dimU,k,alpha,beta);

      alpha=S(k,k+1);
      beta=S(k,k+2);
    }

    { // Make S bi-diagonal again
      for(size_t i0=k0;i0<n-1;i0++){
        for(size_t i1=0;i1<dim[1];i1++){
          if(i0>i1 || i0+1<i1) S(i0,i1)=0;
        }
      }
      for(size_t i0=0;i0<dim[0];i0++){
        for(size_t i1=k0;i1<n-1;i1++){
          if(i0>i1 || i0+1<i1) S(i0,i1)=0;
        }
      }
      for(size_t i=0;i<dim[1]-1;i++){
        if(fabs(S(i,i+1))<=eps*S_max){
          S(i,i+1)=0;
        }
      }
    }
  }
}

#undef U
#undef S
#undef V

template<class T>
inline void svd(char *JOBU, char *JOBVT, int *M, int *N, T *A, int *LDA,
    T *S, T *U, int *LDU, T *VT, int *LDVT, T *WORK, int *LWORK,
    int *INFO){
  assert(*JOBU=='S');
  assert(*JOBVT=='S');
  const size_t dim[2]={std::max(*N,*M), std::min(*N,*M)};
  T* U_=new T[dim[0]*dim[0]]; memset(U_, 0, dim[0]*dim[0]*sizeof(T));
  T* V_=new T[dim[1]*dim[1]]; memset(V_, 0, dim[1]*dim[1]*sizeof(T));
  T* S_=new T[dim[0]*dim[1]];

  const size_t lda=*LDA;
  const size_t ldu=*LDU;
  const size_t ldv=*LDVT;

  if(dim[1]==*M){
    for(size_t i=0;i<dim[0];i++)
    for(size_t j=0;j<dim[1];j++){
      S_[i*dim[1]+j]=A[i*lda+j];
    }
  }else{
    for(size_t i=0;i<dim[0];i++)
    for(size_t j=0;j<dim[1];j++){
      S_[i*dim[1]+j]=A[j*lda+i];
    }
  }
  for(size_t i=0;i<dim[0];i++){
    U_[i*dim[0]+i]=1;
  }
  for(size_t i=0;i<dim[1];i++){
    V_[i*dim[1]+i]=1;
  }

  SVD<T>(dim, U_, S_, V_, (T)-1);

  for(size_t i=0;i<dim[1];i++){ // Set S
    S[i]=S_[i*dim[1]+i];
  }
  if(dim[1]==*M){ // Set U
    for(size_t i=0;i<dim[1];i++)
    for(size_t j=0;j<*M;j++){
      U[j+ldu*i]=V_[j+i*dim[1]]*(S[i]<0.0?-1.0:1.0);
    }
  }else{
    for(size_t i=0;i<dim[1];i++)
    for(size_t j=0;j<*M;j++){
      U[j+ldu*i]=U_[i+j*dim[0]]*(S[i]<0.0?-1.0:1.0);
    }
  }
  if(dim[0]==*N){ // Set V
    for(size_t i=0;i<*N;i++)
    for(size_t j=0;j<dim[1];j++){
      VT[j+ldv*i]=U_[j+i*dim[0]];
    }
  }else{
    for(size_t i=0;i<*N;i++)
    for(size_t j=0;j<dim[1];j++){
      VT[j+ldv*i]=V_[i+j*dim[1]];
    }
  }
  for(size_t i=0;i<dim[1];i++){
    S[i]=S[i]*(S[i]<0.0?-1.0:1.0);
  }

  delete[] U_;
  delete[] S_;
  delete[] V_;
  *INFO=0;
}

int main(){
  typedef double Real_t;
  int n1=45, n2=27;

  // Create matrix
  Real_t* M =new Real_t[n1*n2];
  for(size_t i=0;i<n1*n2;i++) M[i]=rand();

  int m = n2;
  int n = n1;
  int k = (m<n?m:n);
  Real_t* tU =new Real_t[m*k];
  Real_t* tS =new Real_t[k];
  Real_t* tVT=new Real_t[k*n];

  { // Compute SVD
    int INFO=0;
    char JOBU  = 'S';
    char JOBVT = 'S';
    int wssize = 3*(m<n?m:n)+(m>n?m:n);
    int wssize1 = 5*(m<n?m:n);
    wssize = (wssize>wssize1?wssize:wssize1);
    Real_t* wsbuf = new Real_t[wssize];
    svd(&JOBU, &JOBVT, &m, &n, &M[0], &m, &tS[0], &tU[0], &m, &tVT[0], &k, wsbuf, &wssize, &INFO);
    delete[] wsbuf;
  }

  { // Check Error
    Real_t max_err=0;
    for(size_t i0=0;i0<m;i0++)
    for(size_t i1=0;i1<n;i1++){
      Real_t E=M[i1*m+i0];
      for(size_t i2=0;i2<k;i2++) E-=tU[i2*m+i0]*tS[i2]*tVT[i1*k+i2];
      if(max_err<fabs(E)) max_err=fabs(E);
    }
    std::cout<<max_err<<'\n';
  }

  delete[] tU;
  delete[] tS;
  delete[] tVT;
  delete[] M;

  return 0;
}
