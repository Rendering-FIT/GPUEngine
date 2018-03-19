#pragma once

#include <cassert>
#include <cmath>

inline int encodeEdgeMultiplicityToId(unsigned int edgeID, int multiplicity)
{
	assert(multiplicity != 0);
	assert(multiplicity <= 2 && multiplicity >= -2);
	
	int val = edgeID;

	val |= multiplicity < 0 ? (1 << 31) : 0;
	val |= abs(multiplicity) == 2 ? (1 << 30) : 0;

	return val;
}

inline int decodeEdgeMultiplicityFromId(int edgeWithEncodedMultiplicity)
{
	int val = 1;

	const int sign = (edgeWithEncodedMultiplicity & (1<<31)) != 0 ? -1 : 1;
	const int isTwo = (edgeWithEncodedMultiplicity & (1<<30)) != 0;

	return (val + isTwo)*sign;
}

inline int decodeEdgeFromEncoded(int edgeWithEncodedMultiplicity)
{
	return edgeWithEncodedMultiplicity & 0x3FFFFFFF;
}
