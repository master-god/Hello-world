//
//  Copyright (c) 2018, Cem Bassoy, cem.bassoy@gmail.com
//  Copyright (c) 2019, Amit Singh, amitsingh19975@gmail.com
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  Google and Fraunhofer IOSB, Ettlingen, Germany
//


#include <boost/numeric/ublas/tensor.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <iostream>

void multiply_tensors_with_dynamic_order()
{
    using namespace boost::numeric::ublas;

    using format_t = column_major;
    using value_t  = float; // std::complex<double>;
    using tensor_t = dynamic_tensor<value_t,format_t>;
    using shape_t  = typename tensor_t::extents_type;
    using matrix_t = matrix<value_t,format_t>;
    using vector_t = vector<value_t>;

    // Tensor-Vector-Multiplications - Including Transposition
    {

        auto n = shape_t{3,4,2};
        auto A = tensor_t(n,2);
        auto q = 0u; // contraction mode

        // C1(j,k) = T2(j,k) + A(i,j,k)*T1(i);
        q = 1u;
        tensor_t C1 = matrix_t(n[1],n[2],2) + prod(A,vector_t(n[q-1],1),q);

        // C2(i,k) = A(i,j,k)*T1(j) + 4;
        q = 2u;
        tensor_t C2 = prod(A,vector_t(n[q-1],1),q) + 4;

        // C3() = A(i,j,k)*T1(i)*T2(j)*T2(k);  
        tensor_t C3 = prod(prod(prod(A,vector_t(n[0],1),1),vector_t(n[1],1),1),vector_t(n[2],1),1);

        // C4(i,j) = A(k,i,j)*T1(k) + 4;
        q = 1u;
        tensor_t C4 = prod(trans(A,{2,3,1}),vector_t(n[2],1),q) + 4;


        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C1(j,k) = T2(j,k) + A(i,j,k)*T1(i);" << std::endl << std::endl;
        std::cout << "C1=" << C1 << ";" << std::endl << std::endl;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C2(i,k) = A(i,j,k)*T1(j) + 4;" << std::endl << std::endl;
        std::cout << "C2=" << C2 << ";" << std::endl << std::endl;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C3() = A(i,j,k)*T1(i)*T2(j)*T2(k);" << std::endl << std::endl;
        std::cout << "C3()=" << C3(0) << ";" << std::endl << std::endl;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C4(i,j) = A(k,i,j)*T1(k) + 4;" << std::endl << std::endl;
        std::cout << "C4=" << C4 << ";" << std::endl << std::endl;

    }


    // Tensor-Matrix-Multiplications - Including Transposition
    {

        auto n = shape_t{3,4,2};
        auto A = tensor_t(n,2);
        auto m = 5u;
        auto q = 0u; // contraction mode

        // C1(l,j,k) = T2(l,j,k) + A(i,j,k)*T1(l,i);
        q = 1u;
        tensor_t C1 = tensor_t(shape_t{m,n[1],n[2]},2) + prod(A,matrix_t(m,n[q-1],1),q);

        // C2(i,l,k) = A(i,j,k)*T1(l,j) + 4;
        q = 2u;
        tensor_t C2 = prod(A,matrix_t(m,n[q-1],1),q) + 4;

        // C3(i,l1,l2) = A(i,j,k)*T1(l1,j)*T2(l2,k);
        q = 3u;
        tensor_t C3 = prod(prod(A,matrix_t(m+1,n[q-2],1),q-1),matrix_t(m+2,n[q-1],1),q);

        // C4(i,l1,l2) = A(i,j,k)*T2(l2,k)*T1(l1,j);
        tensor_t C4 = prod(prod(A,matrix_t(m+2,n[q-1],1),q),matrix_t(m+1,n[q-2],1),q-1);

        // C5(i,k,l) = A(i,k,j)*T1(l,j) + 4;
        q = 3u;
        tensor_t C5 = prod(trans(A,{1,3,2}),matrix_t(m,n[1],1),q) + 4;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C1(l,j,k) = T2(l,j,k) + A(i,j,k)*T1(l,i);" << std::endl << std::endl;
        std::cout << "C1=" << C1 << ";" << std::endl << std::endl;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C2(i,l,k) = A(i,j,k)*T1(l,j) + 4;" << std::endl << std::endl;
        std::cout << "C2=" << C2 << ";" << std::endl << std::endl;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C3(i,l1,l2) = A(i,j,k)*T1(l1,j)*T2(l2,k);" << std::endl << std::endl;
        std::cout << "C3=" << C3 << ";" << std::endl << std::endl;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C4(i,l1,l2) = A(i,j,k)*T2(l2,k)*T1(l1,j);" << std::endl << std::endl;
        std::cout << "C4=" << C4 << ";" << std::endl << std::endl;
        std::cout << "% C3 and C4 should have the same values, true? " << std::boolalpha << (C3 == C4) << "!" << std::endl;


        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C5(i,k,l) = A(i,k,j)*T1(l,j) + 4;" << std::endl << std::endl;
        std::cout << "C5=" << C5 << ";" << std::endl << std::endl;
    }





    // Tensor-Tensor-Multiplications Including Transposition
    {

        using perm_t = std::vector<std::size_t>;

        auto na = shape_t{3,4,5};
        auto nb = shape_t{4,6,3,2};
        auto A = tensor_t(na,2);
        auto B = tensor_t(nb,3);


        // C1(j,l) = T(j,l) + A(i,j,k)*A(i,j,l) + 5;
        tensor_t C1 = tensor_t(shape_t{na[2],na[2]},2) + prod(A,A,perm_t{1,2}) + 5.0F;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C1(k,l) = T(k,l) + A(i,j,k)*A(i,j,l) + 5;" << std::endl << std::endl;
        std::cout << "C1=" << C1 << ";" << std::endl << std::endl;


        // C2(k,l,m) = T(k,l,m) + A(i,j,k)*B(j,l,i,m) + 5;
        tensor_t C2 = tensor_t(shape_t{na[2],nb[1],nb[3]},2) + prod(A,B,perm_t{1,2},perm_t{3,1}) + 5;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "%  C2(k,l,m) = T(k,l,m) + A(i,j,k)*B(j,l,i,m) + 5;" << std::endl << std::endl;
        std::cout << "C2=" << C2 << ";" << std::endl << std::endl;


        // C3(k,l,m) = T(k,l,m) + A(i,j,k)*trans(B(j,l,i,m),{2,3,1,4})+ 5;
        tensor_t C3 = tensor_t(shape_t{na[2],nb[1],nb[3]},2) + prod(A,trans(B,{2,3,1,4}),perm_t{1,2}) + 5;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "%  C3(k,l,m) = T(k,l,m) + A(i,j,k)*trans(B(j,l,i,m),{2,3,1,4})+ 5;" << std::endl << std::endl;
        std::cout << "C3=" << C3 << ";" << std::endl << std::endl;

    }
}


void multiply_tensors_with_static_order()
{
    using namespace boost::numeric::ublas;

    using format_t  = column_major;
    using value_t   = float; // std::complex<double>;    
    using matrix_t  = matrix<value_t,format_t>;
    using vector_t  = vector<value_t>;
    using tensor2_t = fixed_rank_tensor<value_t,2U>;
    using tensor3_t = fixed_rank_tensor<value_t,3U>;
//    using tensor4_t = fixed_rank_tensor<value_t,4>;
//    using shape_t   = typename tensor_t::extents_type;
//    using shape2_t  = typename tensor2_t::extents_type;
    using shape3_t  = typename tensor3_t::extents_type;
//    using shape4_t  = typename tensor4_t::extents_type;

    // Tensor-Vector-Multiplications - Including Transposition
    // dynamic_extents with static rank
    {

        auto n = shape3_t{3,4,2};
        auto A = tensor3_t(n,value_t(2));
        auto q = 0U; // contraction mode

        // C1(j,k) = T2(j,k) + A(i,j,k)*T1(i);
        q = 1U;
        tensor2_t C1 = matrix_t(n[1],n[2],2) + prod(A,vector_t(n[q-1],1),q);

        // C2(i,k) = A(i,j,k)*T1(j) + 4;
        q = 2U;
        tensor2_t C2 = prod(A,vector_t(n[q-1],1),q) + 4;

        // C3() = A(i,j,k)*T1(i)*T2(j)*T2(k);  
        tensor2_t C3 = prod(prod(prod(A,vector_t(n[0],1),1),vector_t(n[1],1),1),vector_t(n[2],1),1);


        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C1(j,k) = T2(j,k) + A(i,j,k)*T1(i);" << std::endl << std::endl;
        std::cout << "C1=" << C1 << ";" << std::endl << std::endl;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C2(i,k) = A(i,j,k)*T1(j) + 4;" << std::endl << std::endl;
        std::cout << "C2=" << C2 << ";" << std::endl << std::endl;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C3() = A(i,j,k)*T1(i)*T2(j)*T2(k);" << std::endl << std::endl;
        std::cout << "C3()=" << C3(0) << ";" << std::endl << std::endl;

    }

    // Tensor-Matrix-Multiplications - Including Transposition
    // dynamic_extents with static rank
    {

        auto n = shape3_t{3,4,2};
        auto A = tensor3_t(n,value_t(2));
        auto m = 5U;
        auto q = 0U; // contraction mode

        // C1(l,j,k) = T2(l,j,k) + A(i,j,k)*T1(l,i);
        q = 1U;
        tensor3_t C1 = tensor3_t( shape3_t{m,n[1],n[2]},value_t(2) ) + prod(A,matrix_t(m,n[q-1],1),q);

        // C2(i,l,k) = A(i,j,k)*T1(l,j) + 4;
        q = 2U;
        tensor3_t C2 = prod(A,matrix_t(m,n[q-1],1),q) + 4 ;

        // C3(i,l1,l2) = A(i,j,k)*T1(l1,j)*T2(l2,k);
        q = 3U;
        tensor3_t C3 = prod(prod(A,matrix_t(m+1,n[q-2],1),q-1),matrix_t(m+2,n[q-1],1),q) ;

        // C4(i,l1,l2) = A(i,j,k)*T2(l2,k)*T1(l1,j);
        tensor3_t C4 = prod(prod(A,matrix_t(m+2,n[q-1],1),q),matrix_t(m+1,n[q-2],1),q-1) ;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C1(l,j,k) = T2(l,j,k) + A(i,j,k)*T1(l,i);" << std::endl << std::endl;
        std::cout << "C1=" << C1 << ";" << std::endl << std::endl;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C2(i,l,k) = A(i,j,k)*T1(l,j) + 4;" << std::endl << std::endl;
        std::cout << "C2=" << C2 << ";" << std::endl << std::endl;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C3(i,l1,l2) = A(i,j,k)*T1(l1,j)*T2(l2,k);" << std::endl << std::endl;
        std::cout << "C3=" << C3 << ";" << std::endl << std::endl;

        // formatted output
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C4(i,l1,l2) = A(i,j,k)*T2(l2,k)*T1(l1,j);" << std::endl << std::endl;
        std::cout << "C4=" << C4 << ";" << std::endl << std::endl;
        std::cout << "% C3 and C4 should have the same values, true? " << std::boolalpha << (C3 == C4) << "!" << std::endl;

    }

    // Tensor-Tensor-Multiplications Including Transposition
    // dynamic_extents with static rank
    {

//        using perm_t = std::array<std::size_t,2>;

//        auto na = shape3_t{3,4,5};
//        auto nb = shape4_t{4,6,3,2};
//        auto nc = shape2_t{5,5};
//        auto A = tensor3_t(na,2.0F);
//        auto B = tensor4_t(nb,3.0F);
//        auto C = tensor2_t(nc,2.0F);

        // C1(j,l) = T(j,l) + A(i,j,k)*A(i,j,l) + 5;
        // Right now there exist no tensor other than dynamic_extents with 
        // dynamic rank so every tensor times tensor operator automatically
        // to dynamic tensor
//        auto C1 = C + prod(A,A,perm_t{1,2}) + 5.0F;
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "% C1(k,l) = T(k,l) + A(i,j,k)*A(i,j,l) + 5;" << std::endl << std::endl;
//        std::cout << "C1=" << tensor_t(C1) << ";" << std::endl << std::endl;


        // C2(k,l,m) = T(k,l,m) + A(i,j,k)*B(j,l,i,m) + 5;
        // Similar Problem as above
//         tensor_t C2 = tensor_t(shape_t{na[2],nb[1],nb[3]},2.0F) + prod(A,B,perm_t{1,2},perm_t{3,1}) + 5.0F;
        std::cout << "% --------------------------- " << std::endl;
        std::cout << "% --------------------------- " << std::endl << std::endl;
        std::cout << "%  C2(k,l,m) = T(k,l,m) + A(i,j,k)*B(j,l,i,m) + 5;" << std::endl << std::endl;
        //std::cout << "C2=" << C2 << ";" << std::endl << std::endl;

         // C3(k,l,m) = T(k,l,m) + A(i,j,k)*trans(B(j,l,i,m),{2,3,1,4})+ 5;
         // Similar Problem as above
//          tensor_t C3 = tensor_t(shape_t{na[2],nb[1],nb[3]},2.0F) + prod(A,trans(B,{2,3,1,4}),perm_t{1,2}) + 5.0F;
         std::cout << "% --------------------------- " << std::endl;
         std::cout << "% --------------------------- " << std::endl << std::endl;
         std::cout << "%  C3(k,l,m) = T(k,l,m) + A(i,j,k)*trans(B(j,l,i,m),{2,3,1,4})+ 5;" << std::endl << std::endl;
//         std::cout << "C3=" << C3 << ";" << std::endl << std::endl;

    }
}

int main()
{
	multiply_tensors_with_dynamic_order();
	multiply_tensors_with_static_order();
}


