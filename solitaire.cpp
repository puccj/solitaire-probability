#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>

struct Card {
  int n;
  char s;   //D, C, S, B
};

void print(Card* array, int size) {
  std::cout << "\n--Deck--\n";
  for (int i = 0; i < size; i++)
    std::cout << array[i].n << array[i].s << '\n';
}

bool operator==(Card lhs, Card rhs) {
  return (lhs.n == rhs.n || lhs.s == rhs.s);
}


int main() {
  int size = 40;
  int remaning[40] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

  Card deck[size];
  Card initial[size];   //to save the initial deck 

  int nGames = 10000;
  for (int game = 0; game < nGames; game++) {
  //while (size > 2) {
    size = 40;

    //create deck
    for (int i = 0; i < 10; i++) {
    deck[i].n = i+1;
    deck[i].s = 'D';
    }
    for (int i = 10; i < 20; i++) {
      deck[i].n = i-9;
      deck[i].s = 'C';
    }
    for (int i = 20; i < 30; i++) {
      deck[i].n = i-19;
      deck[i].s = 'S';
    }
    for (int i = 30; i < 40; i++) {
      deck[i].n = i-29;
      deck[i].s = 'B';
    }

    //shuffle the deck
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    //std::random_device seed;
    //std::mt19937 g(seed());
    std::shuffle(deck, deck+size, std::default_random_engine(seed));
    
    //set a particular deck
    /*
    Card deck[size] = { {2,'B'}, {2,'C'}, {3,'C'}, {3,'S'}, {9,'C'}, {9,'S'}, {6,'S'}, {3,'B'}, {9,'B'}, {5,'D'}, 
                        {4,'D'}, {9,'D'}, {4,'B'}, {1,'S'}, {6,'D'}, {7,'C'}, {4,'S'}, {5,'B'}, {1,'C'}, {0,'C'}, 
                        {2,'S'}, {7,'S'}, {0,'S'}, {0,'D'}, {7,'D'}, {1,'B'}, {6,'C'}, {5,'S'}, {6,'B'}, {0,'B'}, 
                        {8,'S'}, {7,'B'}, {5,'C'}, {8,'B'}, {8,'D'}, {2,'D'}, {1,'D'}, {8,'C'}, {3,'D'}, {4,'C'}, };
    */

    //print the deck (initial state)
    //print(deck,size);

    //save the initial deck
    // for (int i = 0; i < 40; ++i) {
    //   initial[i] = deck[i];
    // }

    //play a game
    for (int checking = 2; checking < size; checking++) {
      if(deck[checking] == deck[checking-2]) {
        for (int j = checking-1; j < size; j++)  //fa scorrere tutte le carte
          deck[j-1] = deck[j];
        size--;
        checking-=3;
        if (checking < 1)
          checking = 1;
      }
    }
  } //end while

  //print the deck (initial state)
  //print(initial, 40);

  //print the deck (final state)
  //print(deck,size);
  //remaning[size-1]++;

  int max = 0;
  for (int i = 0; i < 40; i++) {
    if (remaning[i] > max)
      max = remaning[i];
  }

  for (int i = 0; i < 40; i++) {
    std::cout << i+1 << ": \t" << remaning[i] << '\t';
    for (int j = 0; j < remaning[i]*200/max; j++) {
      std::cout << 'X';
    }
    std::cout << '\n';
  }
}