#include "Vec.h"
#include <iostream>

int main(){
  Vec vec1(1, 2, 3);
  Vec vec2(2, 1, 0);
  std::cout << vec1.dot(vec2) <<std::endl;
  return 0;
}
