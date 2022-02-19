package math

import "testing"

func TestSubtract(t *testing.T){

    got := Subtract(5, 3)
    want := 2

    if got != want {
        t.Errorf("got %q, wanted %q", got, want)
    }
}