/**
 * 枚举类集合，包含工程用到的所有枚举信息
 */

#ifndef ENUMTYPE_H
#define ENUMTYPE_H

enum class DegreeType
{
	Degree_Two = 2,
	Degree_Three = 3,
};

enum class MethodType
{
	Uniformly_Space =0,
	Chord_Length,
	Centripetal,
	Universal,
};

enum class KnotGenerationType
{
	Uniform = 0,
	Average,
};




#endif // ENUMTYPE_H
