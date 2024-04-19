#pragma once
/*
Copyright  © 2024 Claus Vind-Andreasen

This program is free software; you can redistribute it and /or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU General Public License for more details.
You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111 - 1307 USA
This General Public License does not permit incorporating your program into proprietary programs.If your program is a subroutine library, you may consider it more useful to permit linking proprietary applications with the library.
If this is what you want to do, use the GNU Library General Public License instead of this License.
*/

#ifdef OS_WINDOWS    // windows
#define WIN
typedef unsigned __int64  u64;
typedef __int64  s64;
#else   //linux
#define NOTWIN
#include <stdlib.h>
#include <cstdint>
typedef  uint64_t  u64;
typedef  int64_t  s64;
#endif

#include <vector>


class BitPermutation {

public:

	BitPermutation(){}
	~BitPermutation(){
		permutation.clear();
	}

	inline void SetPermutation(std::vector<int> Spec) {
		/* validation */
		if ((Spec.size() < 2) || (Spec.size() > 64))
		{
			printf("error in specification, size is wrong ");
			return;
		};

		for (int target = 0; target < Spec.size(); target++) {
			int counter = 0;

			for (int i = 0; i < Spec.size(); i++) if (Spec[i] == target) counter++;

			if (counter != 1) {
				printf("error in permutation, missing or dumplicate bit");
				return;
			}
		}

		for (int target = 0; target < Spec.size(); target++) permutation.push_back(Spec[target]);		
	}

	inline u64 Permute(u64 input) {
		u64 output = 0;
		for (int i = 0; i < permutation.size(); i++)
			if (input & (((u64) 1) << i)) output |= (((u64)1) << (permutation[i]));
		return output;
	}
	
private: 

	std::vector<int> permutation;
};