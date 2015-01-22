#include "my_ring_buffer.h"

int main()
{
	ring_buffer<int> rf(3);
	rf.push_back(3);
	rf.push_back(2);
	rf.push_back(1);
	int sum=rf.sum();
	rf.push_back(4);
	ring_buffer<int> rb=rf;
	sum=rf.sum();
	cout<<rf[0]<<rf[1]<<rf[2]<<endl;
	system("pause");
	return 0;
}