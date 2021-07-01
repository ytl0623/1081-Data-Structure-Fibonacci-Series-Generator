// 10727124 劉宇廷 10727139 蘇崇傑 

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

using namespace std ;

typedef char str20[20] ;     // 存字串用

unsigned long long int fibR[93] ;    // fibonacci recursive

unsigned long long int ILtimes = 1 ;     // inner loop times 
unsigned long long int OLtimes = 1 ;     // outer loop times
unsigned long long int IRtimes = 1 ;     // inner recursion times
unsigned long long int ORtimes = 1 ;     // outer recursion times

unsigned long long int temp = 0 ;     // 超過20000次作紀錄
int times = 0 ;     // 每20000記一次
int timeII = 0 ;     // 每400000000記一次

bool Isdigit ( string str ){
  int temp ;
  
  for( int i = 0; i < str.size(); i++ ){
    temp = str[i] ;
    if ( temp >= 48 && temp <= 57 ){     // 數字0-9 
        continue;
    }
    else{
      return false;
    }
    
  }

  return true;

}

int Read() {     // 讀進一個不大於92的數 
  cout << "Input a number: " ;
  
  str20 i ;
  cin >> i ;
  
  while ( ! Isdigit( i ) ){
    cout << "Input a number: " ;
    cin >> i ;
  }
  
  int num = atoi( i ) ;
  return num ;
  
}

void FindfactorL( int i, unsigned long long int num ){
  cout << "[ " << i << "] " << num << " = " ;
  
  unsigned long long int g ;
  g = sqrt(num) ;     // 利用平方根
	
  unsigned long long int lower ;
  unsigned long long int upper ;
  
  while ( g != 0 ){
    if (num % g == 0 ){
      lower = g ;
      upper = num / g ;
      break;
      
    }
    
    g-- ;
    ILtimes++ ;
    
  }


  cout << lower << "*" << upper ;
  cout << "     (Inner loop:  " << ILtimes << "  times)" << endl ;
  ILtimes = 1 ;
	
}

void Iterative() {
  int com = Read() ;
  
  unsigned long long int  fibL[ com ] ;     // fibonacci loop
  
  for (int a = 0 ; a <= com ; a++ ) {     // 初始化 
    fibL[a] = 0 ;
    
  }
  
  fibL [0] = 1 ;
  fibL [1] = 1 ;
  for (int b = 2 ; b <= com ; b++ ){
    fibL[b] = fibL[ b - 1 ] + fibL[ b - 2 ] ;
    
  }
  
  int i = 1 ;
  while ( i <= com ) {
    FindfactorL( i, fibL[i] ) ;
    i++ ;
    OLtimes++ ;
    
  }

  cout << "<Outer loop:  " << OLtimes << "  times>" << endl ;
  OLtimes = 1 ;
  
  delete fibL ;
  
}

int FindfactorR( int n , unsigned long long int root ){
  if ( IRtimes >= 20000 ) {
      times++ ;
      IRtimes = 0 ;
      temp = root ;     // 記憶斷點
      return  1 ;
	  
  }
  else if ( fibR[n] % root == 0 ){
      cout << "[ " << n << "] " << fibR[n] << " = " ;
	  
      unsigned long long int lower = root ;
      unsigned long long int upper = fibR[n] / root ;
      cout << lower << " * " << upper ;
	  
      unsigned long long int RealIRt = timeII * 400000000 + times * 20000 + IRtimes ;
      cout << "     (Inner recursion:  " << RealIRt << "  times)" << endl ;
	  
      IRtimes = 1 ;
      times = 0 ;
      timeII = 0 ;
      return 0 ;
	  
  }
  else if ( fibR[n] % root !=  0 ){
        IRtimes++ ;
        return FindfactorR( n , root - 1 ) ;
		
  }

}

int FindfactorRII( int n , int root ){
    if ( times == 20000 ) {
      timeII++ ;
      times = 0 ;
      return 1 ;
      
    }
    else if ( FindfactorR( n , root ) == 0 ){
      return 0 ;
      
    }
    else if ( FindfactorR( n , root ) == 1 ){
      return FindfactorRII( n , temp  ) ;

    }
    
}

int FindfactorRIII( int n , int root ){
   if ( FindfactorRII( n , root ) == 1 ){
     FindfactorRIII( n , temp ) ;
     
   }
   
}

unsigned long long int FindfibR( int n ) { 
  unsigned long long int root ;

  if ( fibR[n] != 0 ){
    return fibR[n] ;
    
  }
  else if ( n == 0 ){
    fibR[n] = 1 ;
    return 1 ;
    
  }
  
  else if ( n == 1 ){
    ORtimes++ ;
    fibR[n] = 1 ;
    root = sqrt( fibR[n] ) ;
    FindfactorRIII( n, root ) ;
    times = 0 ;
    IRtimes = 1 ;
    timeII = 0 ;
    return 1 ;
    
  }
  else if( n >= 2 ){
    ORtimes++ ;
    fibR[n] = FindfibR( n-2 ) + FindfibR( n-1 ) ;
    root = sqrt( fibR[n] ) ;
    FindfactorRIII( n, root ) ;
    times = 0 ;
    IRtimes = 1 ;
    timeII = 0;
    return fibR[n] ;
    
  }

}

void Recursive(){
  int com = Read() ;
  

  for( int a = 0 ; a <= com ; a++ ){     // 初始化 
    fibR[a] = 0 ;
    
  }
  
  FindfibR( com ) ;
  
  cout << "<Outer recursion:  " << ORtimes << "  times>" << endl ;
  
  ORtimes = 1 ;
  
}



int main() {
    cout << endl << "** Fibonacci Series Generator  **" ;
    cout << endl << "*  0. Quit                      *" ;
    cout << endl << "*  1. Iterative generation      *" ;
    cout << endl << "*  2. Recursive generation      *" ;
    cout << endl << "*********************************" ;
    cout << endl << "Input a command(0,1,2): " ;
    
    str20 command ;
    cin >> command ;     // 輸入指令 
    
    while ( 1 ){    	
      if ( strcmp( command, "1" ) == 0 ){
        Iterative() ;
      }
      else if ( strcmp( command, "2" ) == 0 ){
        Recursive() ;
      }
      else if ( strcmp( command, "0" ) == 0 ){
        break ;
      }
      else
        cout << "command doesn't exist!" << endl ;
      
      cout << endl << "** Fibonacci Series Generator  **" ;
      cout << endl << "*  0. Quit                      *" ;
      cout << endl << "*  1. Iterative generation      *" ;
      cout << endl << "*  2. Recursive generation      *" ;
      cout << endl << "*********************************" << endl ;
      cout << endl << "Input a command(0,1,2): " ;
      
      cin >> command;
      
    }
    
    return 0;
    
}
