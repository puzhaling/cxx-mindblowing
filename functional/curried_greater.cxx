auto greater_curried(double first)
{
  return [first](double second) {
    return first > second;
  };
}

int main() 
{
  bool ans = greater_curried(2)(3);
  return ans;
}
