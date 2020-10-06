void setup() {
  
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  //Test:
  Serial.println();
  Serial.print("shiftRight(5,1) should return 2:          ");
  Serial.println(shiftRight(5,1));
  Serial.print("shiftRight(7,4) should return 0:          ");
  Serial.println(shiftRight(7,4));

  Serial.println();
  Serial.print("shiftLeft(5,2) should return 20:          ");
  Serial.println(shiftLeft(5,2));
  Serial.print("shiftLeft(-1,1) should return -2:        ");
  Serial.println(shiftLeft(-1,1));

  Serial.println();
  Serial.print("hasAOne(4) should return 1:               ");
  Serial.println(hasAOne(4));
  Serial.print("hasAOne(0) should return 0:               ");
  Serial.println(hasAOne(0));

  Serial.println();
  Serial.print("hasAZero(5) should return 1:              ");
  Serial.println(hasAZero(5));
  Serial.print("hasAZero(-1) should return 0:             ");
  Serial.println(hasAZero(-1));
    
  Serial.println();
  Serial.print("leastSigHasAOne(255) should return 1:     ");
  Serial.println(leastSigHasAOne(255));
  Serial.print("leastSigHasAOne(256) should return 0:     ");
  Serial.println(leastSigHasAOne(256));

  Serial.println();
  Serial.print("isNegativeInt(-500) should return 1:      ");
  Serial.println(isNegativeInt(-500));
  Serial.print("isNegativeInt(500) should return 0:       ");
  Serial.println(isNegativeInt(500));

  Serial.println();
  Serial.print("isNegativeLong(-40000) should return 1:   ");
  Serial.println(isNegativeLong(-40000));
  Serial.print("isNegativeLong(40000) should return 0:    ");
  Serial.println(isNegativeLong(40000));

  Serial.println();
  Serial.print("isNegativeChar(-5) should return 1:       ");
  Serial.println(isNegativeChar(-5));
  Serial.print("isNegativeChar(1) should return 0:        ");
  Serial.println(isNegativeChar(1));

  Serial.println();
  Serial.print("negate(-500) should return 500:           ");
  Serial.println(negate(-500));
  Serial.print("negate(500) should return -500:          ");
  Serial.println(negate(500));

//for ease of access, this shows when a test is done
  Serial.println("\n--LOOP COMPLETED--");
}

//
int shiftRight(int num, int n){
  return (num >> n);
}

int shiftLeft(int num, int n){
  return (num << n);
}

// Fix the following functions, using only the bitwise and Boolean operators
int hasAOne(int num) {
  //will have a one so long as it is a non-zero, so use a bool AND to check
  return (num && 1);
}

int hasAZero(int num) {
  //if its inverse isn't all 0's, then it has a 0 normally. So take inverse and check if it is nonzero
  return (num && (~num & 255));
}

int leastSigHasAOne(int num) {
  //least sig makes it odd or even, so just return the last bit
  return (num & 1);
}

//the base t/f for int is 1/0, so just do the operator for the if without writing "if"
int isNegativeInt(int num) {
  return (num < 0);
}

int isNegativeLong(long num) {
  return (num < 0);
}

int isNegativeChar(char num) {
  return (num < 0);
}

int negate(int num) {
  //using bitwise NOT to swap 1's and 0's, making it negatory. Need to add one to fix computing error
  return (~num + 1);
}
