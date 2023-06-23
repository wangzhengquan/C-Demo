
#include "usg_common.h"

int main()
{
	std::vector<int> v = {7, 5, 16, 8};

	// Insert an integer before 16 by searching
  auto it = std::find(v.begin(), v.end(), 16);
  if (it != v.end())
      v.insert(it, 42);

  // use a lambda expression to count elements divisible by 4.
  int count_div4 = std::count_if(v.begin(), v.end(), [](int i) { return i % 4 == 0; });
  std::cout << "numbers divisible by four: " << count_div4 << '\n';



  std::vector<int> v2(16);
  std::generate(v2.begin(), v2.end(), rand);
  std::sort(v2.begin(), v2.end());
  std::cout << "v2: " ;
  std::copy(v2.begin(), v2.end(), std::ostream_iterator<int>(std::cout, ","));
	std::cout << std::endl;
	
}