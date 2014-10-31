#include <geSG/AttribType.h>

using namespace ge::sg;

const AttribType AttribType::Invalid{GLType::INVALID,0,0,NOT_DEFINED};
const AttribType AttribType::Empty{GLType::EMPTY,0,0,NOT_DEFINED};

const AttribType AttribType::Byte {GLType::BYTE,1,1,USE_IFORMAT};
const AttribType AttribType::BVec2{GLType::BYTE,2,2,USE_IFORMAT};
const AttribType AttribType::BVec3{GLType::BYTE,3,3,USE_IFORMAT};
const AttribType AttribType::BVec4{GLType::BYTE,4,4,USE_IFORMAT};

const AttribType AttribType::UByte {GLType::UNSIGNED_BYTE,1,1,USE_IFORMAT};
const AttribType AttribType::UBVec2{GLType::UNSIGNED_BYTE,2,2,USE_IFORMAT};
const AttribType AttribType::UBVec3{GLType::UNSIGNED_BYTE,3,3,USE_IFORMAT};
const AttribType AttribType::UBVec4{GLType::UNSIGNED_BYTE,4,4,USE_IFORMAT};

const AttribType AttribType::Short{GLType::SHORT,1,2*1,USE_IFORMAT};
const AttribType AttribType::SVec2{GLType::SHORT,2,2*2,USE_IFORMAT};
const AttribType AttribType::SVec3{GLType::SHORT,3,2*3,USE_IFORMAT};
const AttribType AttribType::SVec4{GLType::SHORT,4,2*4,USE_IFORMAT};

const AttribType AttribType::UShort{GLType::UNSIGNED_SHORT,1,2*1,USE_IFORMAT};
const AttribType AttribType::USVec2{GLType::UNSIGNED_SHORT,2,2*2,USE_IFORMAT};
const AttribType AttribType::USVec3{GLType::UNSIGNED_SHORT,3,2*3,USE_IFORMAT};
const AttribType AttribType::USVec4{GLType::UNSIGNED_SHORT,4,2*4,USE_IFORMAT};

const AttribType AttribType::Int  {GLType::INT,1,4*1,USE_IFORMAT};
const AttribType AttribType::IVec2{GLType::INT,2,4*2,USE_IFORMAT};
const AttribType AttribType::IVec3{GLType::INT,3,4*3,USE_IFORMAT};
const AttribType AttribType::IVec4{GLType::INT,4,4*4,USE_IFORMAT};

const AttribType AttribType::UInt {GLType::UNSIGNED_INT,1,4*1,USE_IFORMAT};
const AttribType AttribType::UVec2{GLType::UNSIGNED_INT,2,4*2,USE_IFORMAT};
const AttribType AttribType::UVec3{GLType::UNSIGNED_INT,3,4*3,USE_IFORMAT};
const AttribType AttribType::UVec4{GLType::UNSIGNED_INT,4,4*4,USE_IFORMAT};

const AttribType AttribType::Float{GLType::FLOAT,1,4*1,USE_FORMAT};
const AttribType AttribType::Vec2 {GLType::FLOAT,2,4*2,USE_FORMAT};
const AttribType AttribType::Vec3 {GLType::FLOAT,3,4*3,USE_FORMAT};
const AttribType AttribType::Vec4 {GLType::FLOAT,4,4*4,USE_FORMAT};

const AttribType AttribType::Double{GLType::DOUBLE,1,8*1,USE_LFORMAT};
const AttribType AttribType::DVec2 {GLType::DOUBLE,2,8*2,USE_LFORMAT};
const AttribType AttribType::DVec3 {GLType::DOUBLE,3,8*3,USE_LFORMAT};
const AttribType AttribType::DVec4 {GLType::DOUBLE,4,8*4,USE_LFORMAT};

const AttribType AttribType::Half {GLType::HALF_FLOAT,1,2*1,USE_FORMAT};
const AttribType AttribType::HVec2{GLType::HALF_FLOAT,2,2*2,USE_FORMAT};
const AttribType AttribType::HVec3{GLType::HALF_FLOAT,3,2*3,USE_FORMAT};
const AttribType AttribType::HVec4{GLType::HALF_FLOAT,4,2*4,USE_FORMAT};

const AttribType AttribType::Byte_3_3_2            {GLType::UNSIGNED_BYTE_3_3_2,           3,1,INTEGER_NORMALIZE};
const AttribType AttribType::Byte_2_3_3_Rev        {GLType::UNSIGNED_BYTE_2_3_3_REV,       3,1,INTEGER_NORMALIZE};
const AttribType AttribType::Short_5_6_5           {GLType::UNSIGNED_SHORT_5_6_5,          3,2,INTEGER_NORMALIZE};
const AttribType AttribType::Short_5_6_5_Rev       {GLType::UNSIGNED_SHORT_5_6_5_REV,      3,2,INTEGER_NORMALIZE};
const AttribType AttribType::Short_4_4_4_4         {GLType::UNSIGNED_SHORT_4_4_4_4,        4,2,INTEGER_NORMALIZE};
const AttribType AttribType::Short_4_4_4_4_Rev     {GLType::UNSIGNED_SHORT_4_4_4_4_REV,    4,2,INTEGER_NORMALIZE};
const AttribType AttribType::Short_5_5_5_1         {GLType::UNSIGNED_SHORT_5_5_5_1,        4,2,INTEGER_NORMALIZE};
const AttribType AttribType::Short_1_5_5_5_Rev     {GLType::UNSIGNED_SHORT_1_5_5_5_REV,    4,2,INTEGER_NORMALIZE};
const AttribType AttribType::Int_8_8_8_8           {GLType::UNSIGNED_INT_8_8_8_8,          4,4,INTEGER_NORMALIZE};
const AttribType AttribType::Int_8_8_8_8_Rev       {GLType::UNSIGNED_INT_8_8_8_8_REV,      4,4,INTEGER_NORMALIZE};
const AttribType AttribType::Int_10_10_10_2        {GLType::UNSIGNED_INT_10_10_10_2,       4,4,INTEGER_NORMALIZE};
const AttribType AttribType::Int_2_10_10_10_Rev    {GLType::UNSIGNED_INT_2_10_10_10_REV,   4,4,INTEGER_NORMALIZE};
const AttribType AttribType::Int_24_8              {GLType::UNSIGNED_INT_24_8,             2,4,INTEGER_NORMALIZE};
const AttribType AttribType::Int_10F_11F_11F_Rev   {GLType::UNSIGNED_INT_10F_11F_11F_REV,  3,4,INTEGER_NORMALIZE};
const AttribType AttribType::Int_5_9_9_9_Rev       {GLType::UNSIGNED_INT_5_9_9_9_REV,      4,4,INTEGER_NORMALIZE};
const AttribType AttribType::Float_32_UInt_24_8_Rev{GLType::FLOAT_32_UNSIGNED_INT_24_8_REV,2,8,INTEGER_NORMALIZE};

const AttribType AttribType::Mat2{GLType::MAT2,4, 4*4, NOT_DEFINED};
const AttribType AttribType::Mat3{GLType::MAT3,9, 4*9, NOT_DEFINED};
const AttribType AttribType::Mat4{GLType::MAT4,16,4*16,NOT_DEFINED};

const AttribType AttribType::Mat2x3{GLType::MAT2X3,6, 4*6, NOT_DEFINED};
const AttribType AttribType::Mat2x4{GLType::MAT2X4,8, 4*8, NOT_DEFINED};
const AttribType AttribType::Mat3x2{GLType::MAT3X2,6, 4*6, NOT_DEFINED};
const AttribType AttribType::Mat3x4{GLType::MAT3X4,12,4*12,NOT_DEFINED};
const AttribType AttribType::Mat4x2{GLType::MAT4X2,8, 4*8, NOT_DEFINED};
const AttribType AttribType::Mat4x3{GLType::MAT4X3,12,4*12,NOT_DEFINED};

const AttribType AttribType::DMat2{GLType::DMAT2,4, 8*4, NOT_DEFINED};
const AttribType AttribType::DMat3{GLType::DMAT3,9, 8*9, NOT_DEFINED};
const AttribType AttribType::DMat4{GLType::DMAT4,16,8*16,NOT_DEFINED};

const AttribType AttribType::DMat2x3{GLType::DMAT2X3,6, 8*6, NOT_DEFINED};
const AttribType AttribType::DMat2x4{GLType::DMAT2X4,8, 8*8, NOT_DEFINED};
const AttribType AttribType::DMat3x2{GLType::DMAT3X2,6, 8*6, NOT_DEFINED};
const AttribType AttribType::DMat3x4{GLType::DMAT3X4,12,8*12,NOT_DEFINED};
const AttribType AttribType::DMat4x2{GLType::DMAT4X2,8, 8*8, NOT_DEFINED};
const AttribType AttribType::DMat4x3{GLType::DMAT4X3,12,8*12,NOT_DEFINED};
