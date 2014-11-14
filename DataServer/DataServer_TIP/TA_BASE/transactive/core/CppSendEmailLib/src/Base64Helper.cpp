#include "core/CppSendEmailLib/src/Base64Helper.h"

//
NS_BEGIN(TA_Base_Core)


Base64Helper::Base64Helper()
{

}


Base64Helper::~Base64Helper()
{

}


const std::string Base64Helper::m_strBase64EnCodeChars = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

const char Base64Helper::m_szBase64DeCodeChars[] = 
{
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
	-1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
	-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1
};

std::string Base64Helper::encode(const std::string in_str)
{
	std::string out_str;
	unsigned char c1;
	unsigned char c2;
	unsigned char c3;
	int nIndex = 0;
	int nLength = in_str.length();

	while ( nIndex<nLength )
	{
		// read the first byte
		c1 = in_str[nIndex++];
		if ( nIndex==nLength )       // pad with "="
		{
			out_str += m_strBase64EnCodeChars[ c1>>2 ];
			out_str += m_strBase64EnCodeChars[ (c1&0x3)<<4 ];
			out_str += "==";
			break;
		}

		// read the second byte
		c2 = in_str[nIndex++];
		if ( nIndex==nLength )       // pad with "="
		{
			out_str += m_strBase64EnCodeChars[ c1>>2 ];
			out_str += m_strBase64EnCodeChars[ ((c1&0x3)<<4) | ((c2&0xF0)>>4) ];
			out_str += m_strBase64EnCodeChars[ (c2&0xF)<<2 ];
			out_str += "=";
			break;
		}

		// read the third byte
		c3 = in_str[nIndex++];
		// convert into four bytes string
		out_str += m_strBase64EnCodeChars[ c1>>2 ];
		out_str += m_strBase64EnCodeChars[ ((c1&0x3)<<4) | ((c2&0xF0)>>4) ];
		out_str += m_strBase64EnCodeChars[ ((c2&0xF)<<2) | ((c3&0xC0)>>6) ];
		out_str += m_strBase64EnCodeChars[ c3&0x3F ];
	}

	return out_str;
}

std::string Base64Helper::decode(const std::string in_str)
{
	std::string out_str;
	char c1;
	char c2;
	char c3;
	char c4;
	int nIndex = 0;
	int nLength = in_str.length();

	while ( nIndex<nLength)
	{
		// read the first byte
		do {
			c1 = m_szBase64DeCodeChars[ in_str[nIndex++] ];
		} while ( nIndex<nLength && c1==-1);

		if ( c1==-1)
			break;

		// read the second byte
		do {
			c2 = m_szBase64DeCodeChars[ in_str[nIndex++] ];
		} while ( nIndex<nLength && c2==-1);

		if ( c2==-1 )
			break;

		// assamble the first byte
		out_str += char( (c1<<2) | ((c2&0x30)>>4) );

		// read the third byte
		do {
			c3 = in_str[nIndex++];
			if ( c3==61 )       // meet with "=", break
				return out_str;
			c3 = m_szBase64DeCodeChars[ c3 ];
		} while ( nIndex<nLength && c3==-1);

		if ( c3==-1 )
			break;

		// assamble the second byte
		out_str += char( ((c2&0XF)<<4) | ((c3&0x3C)>>2) );

		// read the fourth byte
		do {
			c4 = in_str[nIndex++];
			if ( c4==61 )       // meet with "=", break
				return out_str;
			c4 = m_szBase64DeCodeChars[ c4 ];
		} while ( nIndex<nLength && c4==-1 );

		if ( c4==-1 )
			break;

		// assamble the third byte
		out_str += char( ((c3&0x03)<<6) | c4 );
	}

	return out_str;
}

NS_END(TA_Base_Core)



#if 0

Base64是网络上最常见的用于传输8Bit字节代码的编码方式之一，大家可以查看RFC2045～RFC2049，上面有MIME的详细规范。

Base64要求把每三个8Bit的字节转换为四个6Bit的字节（3*8 = 4*6 = 24），然后把6Bit再添两位高位0，组成四个8Bit的字节，也就是说，转换后的字符串理论上将要比原来的长1/3


我们用一个码表来得到我们想要的字符串（也就是最终的Base64编码），这个表是这样的：（摘自RFC2045）


Table 1: The Base64 Alphabet

Value Encoding  Value Encoding  Value Encoding  Value Encoding
0 A            17 R            34 i            51 z
1 B            18 S            35 j            52 0
2 C            19 T            36 k            53 1
3 D            20 U            37 l            54 2
4 E            21 V            38 m            55 3
5 F            22 W            39 n            56 4
6 G            23 X            40 o            57 5
7 H            24 Y            41 p            58 6
8 I            25 Z            42 q            59 7
9 J            26 a            43 r            60 8
10 K            27 b            44 s            61 9
11 L            28 c            45 t            62 +
12 M            29 d            46 u            63 /
13 N            30 e            47 v
14 O            31 f            48 w         (pad) =
15 P            32 g            49 x
16 Q            33 h            50 y


让我们再来看一个实际的例子，加深印象！

转换前	10101101	10111010	01110110	
转换后	00101011	00011011	00101001	00110110
十进制	43	        27	        41	        54
对应码表中的值	r	b	p	2


所以上面的24位编码，编码后的Base64值为 rbp2
解码同理，把 rbq2 的二进制位连接上再重组得到三个8位值，得出原码。
（解码只是编码的逆过程，在此我就不多说了，另外有关MIME的RFC还是有很多的，如果需要详细情况请自行查找。


#endif








