#include<iostream>
#include<cmath>

char *encode(char *plaintext, unsigned long key );
char *decode( char *cihpertext, unsigned long key );

char *encode(char *plaintext, unsigned long key )
{
	unsigned char s[256];
	std::size_t strlen;
	unsigned int i{0}, j{0}, a{0};
	unsigned long newlen;

	for(strlen = 0; plaintext[strlen]; strlen++); //length without the null character

	newlen=(std::ceil(strlen/4.0))*4+1;

	//std::cout<<newlen;
	char four_multiple[newlen];
	unsigned char xor_array[newlen];
	xor_array[newlen-1]= '\0';

	for(std::size_t k{0}; k<newlen; k++)
	{
		if(k<strlen){
			four_multiple[k]=plaintext[k];
		}else{
			four_multiple[k]='\0';
	}
	}

	for(std::size_t k{0}; k<256; k++)
	{
		s[k] = k;

	}
	while(a<256)
	{
		unsigned int k=i%64;
		j= (j+s[i]+((key>>k)&1L))%256;
		unsigned int temp=s[j];
		s[j]=s[i];
		s[i]=temp;
		i=(i+1)%256;
		a++;
	}

	//std::cout<<static_cast<unsigned int>(xor_array[newlen-1])<<std::endl;
	for(std::size_t k{0}; k<(newlen-1); k++)
	{

		i=(i+1)%256;
		j=(j+s[i])%256;
		unsigned char temp=s[j];
		s[j]=s[i];
		s[i]=temp;
		std::size_t r= (s[i]+s[j])%256;

		unsigned char R=s[r];
		std::cout<<static_cast<unsigned int>(R)<<" ";

	//		std::cout<< static_cast<unsigned int>(R)<<" "<<static_cast;
		xor_array[k]= R ^ four_multiple[k];
	}
	//for(std::size_t k{0}; k<newlen;k++)
	//{
		//std::cout<<static_cast<unsigned int>(xor_array[k])<<" ";
	//}


	//ASCII ARMOUR//
	std::size_t base_85_len{5*(newlen/4) + 1};
	unsigned int base_85;
	 char *armour_arr{ new char[base_85_len]{}};


	for (std::size_t x{0}; x<(newlen/4); x++)
	{
		base_85=	(xor_array[4*x]<<24)+
					(xor_array[4*x+1]<<16)+
					(xor_array[4*x+2]<<8)+
					(xor_array[4*x+3]);
		std::cout<<base_85<<std::endl;
		armour_arr[5*x+4]=(base_85%85) +'!';
		base_85/=85;
		armour_arr[5*x+3]=(base_85%85) +'!';
		base_85/=85;
		armour_arr[5*x+2]=(base_85%85) +'!';
		base_85/=85;
		armour_arr[5*x+1]=(base_85%85) +'!';
		base_85/=85;
		armour_arr[5*x]=(base_85%85) +'!';
		base_85/=85;
	}

	armour_arr[base_85_len]='\0';
	//print armour

	//for(std::size_t y{0}; y<base_85_len; y++)
		//std::cout<<armour_arr[y];

	return armour_arr;

}


char *decode( char *cihpertext, unsigned long key )
{
	std::size_t cipher_len=0;

	for(cipher_len; cihpertext[cipher_len]; cipher_len++);
//	std::cout<<cipher_len; //tested and wokrs, without including the null char

	unsigned int dec_val;
	std::size_t size_dec=(4*cipher_len/5);
	char *dec_array{new  char[size_dec]};
	for(std::size_t k=0; k<cipher_len/5; k++)
	{
		dec_val=(cihpertext[5*k+0]-'!')*(pow(85, 4)) +
				(cihpertext[5*k+1]-'!')*(pow(85, 3)) +
				(cihpertext[5*k+2]-'!')*(pow(85, 2)) +
				(cihpertext[5*k+3]-'!')*(pow(85, 1)) +
				(cihpertext[5*k+4]-'!')*(pow(85, 0));
		dec_array[4*k+0]=dec_val>>24;
		dec_array[4*k+1]=dec_val>>16;
		dec_array[4*k+2]=dec_val>> 8;
		dec_array[4*k+3]=dec_val;
	}
	//	for(std::size_t k{0}; k<cipher_len*4/5; ++k){
	//		std::cout<<static_cast<unsigned int>(dec_array[k])<<" ";
	//	}

	unsigned char s[256];
	unsigned int i{0}, j{0}, a{0};


		for(std::size_t k{0}; k<256; k++)
		{
			s[k] = k;

		}
		while(a<256)
		{
			unsigned int k=i%64;
			j= (j+s[i]+((key>>k)&1L))%256;
			unsigned int temp=s[j];
			s[j]=s[i];
			s[i]=temp;
			i=(i+1)%256;
			a++;
		}

		// std::cout<<static_cast<unsigned int>(xor_array[newlen-1])<<std::endl;
		for(std::size_t k{0}; k<size_dec; k++)
		{

			i=(i+1)%256;
			j=(j+s[i])%256;
			unsigned char temp=s[j];
			s[j]=s[i];
			s[i]=temp;
			std::size_t r= (s[i]+s[j])%256;
			unsigned char R=s[r];
			// std::cout<< static_cast<unsigned int>(R)<<" "<<static_cast;
			dec_array[k]= R ^ dec_array[k];
		}

		//for(std::size_t k{0}; k<size_dec; k++)
		//{
			//std::cout<<dec_array[k];
		//}
		dec_array[size_dec]='\0';
	return dec_array;

}


int main();

int main(){
	char str0[]{"study"};
	//std::cout << "\"" << str0 << "\"" << std::endl;
	char * ciphertext = encode( str0, 3408 );
	std::cout<< "\"" << ciphertext << "\"" << std::endl;
	char * idk=decode( ciphertext, 3408 );
	std::cout<<idk<<std::endl;
	delete[] ciphertext;
	ciphertext=nullptr;
	delete[] idk;
	idk=nullptr;
	return 0;
}
