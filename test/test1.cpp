#include <stdio.h>
#include <string.h>
#include <map>
#include <queue>
#include <memory>
int main(int argc, char *argv[]) {
  const char *  arr[] = {"hello", "world"};
  std::map<uint32_t, std::shared_ptr<std::queue<int> > > _pending_map{};
  for (int i=0; i<2; i++)
 	  printf("%s\n", arr[i]);
}
