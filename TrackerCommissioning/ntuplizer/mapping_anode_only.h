#ifndef MAPPING_ANODE_ONLY_H_
#define MAPPING_ANODE_ONLY_H_

//compile with g++ mapping_anode_only.c -o mapping
//or execute with root


/*

C0 cassettes are mapped as follows:

[anode side]
      0     1     2     3

   |-----|-----|-----|-----|
1    B1    A1    B1    A1
   |-----|-----|-----|-----|
2    B2    A2    B2    A2
   |-----|-----|-----|-----|

   |-----|-----|-----|-----|

   |-----|-----|-----|-----|
9    B9    A9    B9    A9
   |-----|-----|-----|-----|

 */

// Mapping between Feed Through and the cassette
void FT_to_cassette(int FT_i, int FT_pin, int& col, int& row){

  int FT_pin_to_col[2][23] =
    { //anode (LARGE connector)
      {-1,1,1,1,1,1,1,1,-1,1,1,0,0,-1,0,0,0,0,0,0,0,-1,-1},
      {-1,3,3,3,3,3,3,3,-1,3,3,2,2,-1,2,2,2,2,2,2,2,-1,-1}
    };
  int FT_pin_to_row[2][23] =
    { //anode (large connector)
      {-1,1,2,3,4,5,6,7,-1,8,9,1,2,-1,3,4,5,6,7,8,9,-1,-1},
      {-1,1,2,3,4,5,6,7,-1,8,9,1,2,-1,3,4,5,6,7,8,9,-1,-1}
    };

  if(FT_i<0 | FT_i>1 | FT_pin<0 | FT_pin>22 ){
    col = -1;
    row = -1;
    return;
  }

  col = FT_pin_to_col[FT_i][FT_pin];
  row = FT_pin_to_row[FT_i][FT_pin];
  return;

}

// Mapping between the HV Mother Board and the Feed Through
void HVMB_to_FT(int DB_num, int DB_pin, int &FT_i, int &FT_pin){
  int HVMB_to_FT_pin[5][8]=
    {  //anode
      {-1, 2, 3, 4, 5, 6, 7, 9},
      {-1,12,14,15,16,17,18,19},
      { 1,10,11,20, 1,10,11,20},
      {-1, 2, 3, 4, 5, 6, 7, 9},
      {-1,12,14,15,16,17,18,19}
    };

  int HVMB_to_FT_i[5][8]=
    {  //anode
      {-1, 0, 0, 0, 0, 0, 0, 0},
      {-1, 0, 0, 0, 0, 0, 0, 0},
      { 0, 0, 0, 0, 1, 1, 1, 1},
      {-1, 1, 1, 1, 1, 1, 1, 1},
      {-1, 1, 1, 1, 1, 1, 1, 1}
    };


  if(DB_num<0 | DB_num>4 | DB_pin<0 | DB_pin>7 ){
    FT_pin = -1;
    FT_i = -1;
    return;
  }

  FT_pin = HVMB_to_FT_pin[DB_num][DB_pin];
  FT_i = HVMB_to_FT_i[DB_num][DB_pin];
  return;
}

// Mapping between the HV Mother Board and the Channel
void Ch_num_to_HVMB(int Ch_num, int &DB_num, int &DB_pin){
  int Ch_num_to_HVMB_DB_pin[40]= {7,6,5,4,3,2,1,0,7,6,5,4,3,2,1,0,7,6,5,4,3,2,1,0,7,6,5,4,3,2,1,0,7,6,5,4,3,2,1,0};
  int Ch_num_to_HVMB_DB_num[40]= {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4};

  if(Ch_num<0 | Ch_num>39){
    DB_num = -1;
    DB_pin = -1;
    return;
  }

  DB_num = Ch_num_to_HVMB_DB_num[Ch_num];
  DB_pin = Ch_num_to_HVMB_DB_pin[Ch_num];
}

// Mapping between the channel and the ASIC number and channel
void Geiger_to_Ch_num(int Asic_num, int Asic_ch, int& Ch_num){

  if(Asic_num<0 | Asic_num > 9 | Asic_ch<0 | Asic_ch > 3) {
    Ch_num = -1;
  } else{
    Ch_num = Asic_num*4 + Asic_ch;
  }
}

void Geiger_to_cassette(int Asic_num, int Asic_ch, int& col, int& row){
  int Ch_num, DB_num, DB_pin, FT_i, FT_pin;

  // ASIC -> Channel Number
  Geiger_to_Ch_num(Asic_num, Asic_ch, Ch_num);

  Ch_num_to_HVMB(Ch_num, DB_num, DB_pin);

  HVMB_to_FT(DB_num, DB_pin, FT_i, FT_pin);

  FT_to_cassette(FT_i, FT_pin, col, row);
}

#endif
