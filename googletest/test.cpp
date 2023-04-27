#include<gtest/gtest.h>
 
int add(int a,int b)
{
    return a+b;
}

int sub(int a, int b)
{
	return a-b;
}

int circle()
{
	char c;
	std::cin >> c;
	if(c == 27)
	{
		return 1 ;
	}

	
	return 0;
}
 
TEST(testCase,test0)
{
    EXPECT_EQ(circle(),1);
   // EXPECT_EQ(sub(2,1),22);
}
int main(int argc,char **argv)
{
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
