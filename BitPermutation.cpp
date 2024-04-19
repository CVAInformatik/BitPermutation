// BitPermuatation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <vector>
#include <iostream>

#include "BitPermutation.h"


class GrayCodeGeneratorClass
{
public:
	GrayCodeGeneratorClass() : mask(0), state(0) {};
	~GrayCodeGeneratorClass() {};

	inline void Init(unsigned int _width, u64 FirstValue = 0) {

		if (0 < _width && _width < 65) {
			switch (_width)
			{
			case 64: mask = 0xFFFFFFFFFFFFFFFF;
				break;
			default: mask = ((u64)1) << _width;
				mask--;
				break;
			}

			state = (FirstValue & mask);
			/*
			   'state' is now initialized to
					 Firstvalue ^ [Firstvalue/2] ^  [Firstvalue/4] ^ [Firstvalue/8] ^.......
			   an infinite sum, where the terms eventurally become 0, so we can stop there
				(note:  [X] is the integer part of X )

			   The output :  state ^ (state >>1)  then becomes

					 Firstvalue ^ [Firstvalue/2] ^  [Firstvalue/4] ^ [Firstvalue/8] ^.......
				^                 [Firstvalue/2] ^  [Firstvalue/4] ^ [Firstvalue/8] ^.......
				where all terms except the first cancel..
			*/
			u64 temp = (FirstValue & mask) >> 1;
			while (temp) {
				state ^= temp;
				temp = temp >> 1;
			}

		}
		else {
			mask = 0;
			state = 0;
		}
	};

	/*
	   the order 'state' is incremented  or decremented below is a choice.
	   Not sure there is a 'right' way....
	*/
	inline u64 Next() {
		u64 res = state ^ (state >> 1);
		state = (state + 1) & mask;
		return mask & res;
	};

	inline u64 Previous() {
		if (state)  state = (state - 1) & mask;
		else 		state = mask;
		return mask & (state ^ (state >> 1));
	};

private:
	u64 state;
	u64 mask;
};



void putBit(int w, u64 x)
{
    if (w > 1)
    {
        putBit(w - 1, x >> 1);
    }
    printf("%c", x & 1 ? '1' : '0');

}


int main()
{

    BitPermutation perm;
    GrayCodeGeneratorClass gc;

    gc.Init(6);

    std::vector<int> p;

    p.push_back(4); // send bit 0 -> 4
    p.push_back(3); // send bit 1 -> 3
    p.push_back(5); // send bit 2 -> 5
    p.push_back(1); // send bit 3 -> 1
    p.push_back(2); // send bit 4 -> 2
    p.push_back(0); // send bit 5 -> 0

    perm.SetPermutation(p);
    for (int  i = 0; i < 65; i++) {
        printf("%4X ", (unsigned int ) i);
        u64 v = gc.Next();
        putBit((int) p.size(), v);
        printf("  ");
        putBit((int) p.size(), perm.Permute(v));
        printf("\n");
    }

}
