#FAIL: (0)
AG(~(~inr<3> & ~inr<2> & ~inr<1> & ~inr<0>) -> ~E spl U (~inr<3> & ~inr<2> & ~inr<1> & ~inr<0>))
#FAIL: (1)
AG((~inr<3> & ~inr<2> & ~inr<1> & ~inr<0>) -> ~E spl U ~(~inr<3> & ~inr<2> &
~inr<1> & ~inr<0>))
#FAIL: (2)
AG((~inr<3> & ~inr<2> & ~inr<1> & inr<0>) -> ~E spl U (~inr<3> & ~inr<2> & inr<1> & inr<0>))
#PASS: (3)
EF((~inr<3> & ~inr<2> & ~inr<1> & inr<0>) & E spl U (~inr<3> & ~inr<2> & inr<1> & inr<0>))
#PASS: (4)
EF(E spl U (~inr<3> & ~inr<2> & inr<1> & inr<0>))
