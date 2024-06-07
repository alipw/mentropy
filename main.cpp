#include<iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<utility>
#include<algorithm>
#include<cmath>


// print the most frequent data
void debug_map(std::map<char,float> mpc){
  std::vector<std::pair<float,char>> mpcc;
  for(auto [c, d] : mpc) {
    mpcc.push_back({d, c});
  }

  sort(mpcc.rbegin(), mpcc.rend());
  float sm = 0;
  for(auto [d, c]: mpcc) {
    printf("%f -> %c\n", d, c);
    sm += d;
  }
}

std::map<char,float> get_p(std::map<char,int> &mpc, int sz = -1) {
  int ttal = 0;
  std::map<char,float> mpp;

  if(sz == -1) {
    for(auto [c, d] : mpc) {
      ttal += d;
    }
  } else {
    ttal = sz;
  }

  for(auto [c, d] : mpc) {
    mpp[c] = float(d) / float(ttal);
  }

  return mpp;
}

int main(int argc, char* argv[]){
  std::string filename;
  if(argc > 1) {
    filename = argv[1];
  } else {
    printf("usage: mentropy <filename>\n");
    return 0;
  }
  std::fstream file(filename);

  if(!file.is_open()){
    printf("file %s does not exist\n", argv[1]);
    return 0;
  }

  std::map<char,int> mpc;
  char c;
  int sc = 0;
  while(file.get(c)) {
    mpc[c]++;
    sc++;
  }

  std::map<char, float> map_prob = get_p(mpc);
  debug_map(map_prob);
  float H = 0;
  for(auto [c, p] : map_prob) {
    H += p * log2(p);
  }

  printf("\nfile: %s\naverage entropy: %f bits per symbol\n", argv[1], -H);
  printf("total symbol: %d\ntotal unique symbol: %d\n", sc, mpc.size());
  printf("file can theoretically be compressed to as low as %d bytes\n", int(ceil(float(sc) * -H / 8.f)));
  return 0;
}

