void writeActivities(string filename,
		     double *Activities_Ext, double *Activities_Ext_Err,
		     double *Activities_Rad, double *Activities_Rad_Err,
		     double *Activities_Int, double *Activities_Int_Err,
		     double *Activities_Sig, double *Activities_Sig_Err,
		     double *AdjustActs,     double *AdjustActs_Err){

  ofstream outfile;

  outfile.open(filename.c_str());

  if(outfile.is_open()){

    for(int i = 0; i < 23; i++){
      outfile << "Activities_Ext[" << i << "]= " << Activities_Ext[i] << " " << Activities_Ext_Err[i] << endl; 
    }

    for(int i = 0; i < 17; i++){
      outfile << "Activities_Rad[" << i << "]= " << Activities_Rad[i] << " " << Activities_Rad_Err[i] << endl; 
    }

    for(int i = 0; i < 9; i++){
      outfile << "Activities_Int[" << i << "]= " << Activities_Int[i] << " " << Activities_Int_Err[i] << endl; 
    }

    for(int i = 0; i < 2; i++){
      outfile << "Activities_Sig[" << i << "]= " << Activities_Sig[i] << " " << Activities_Sig_Err[i] << endl; 
    }

    for(int i = 0; i < 44; i++){
      outfile << "AdjustActs[" << i << "]= " << AdjustActs[i] << " " << AdjustActs_Err[i] << endl; 
    }

    outfile.close();

  }
}

void readActivities(string filename,
		    double *Activities_Ext, double *Activities_Ext_Err,
		    double *Activities_Rad, double *Activities_Rad_Err,
		    double *Activities_Int, double *Activities_Int_Err,
		    double *Activities_Sig, double *Activities_Sig_Err,
		    double *AdjustActs,     double *AdjustActs_Err){

  ifstream infile;

  infile.open(filename.c_str());

  if(infile.is_open()){
    string tmp;

    for(int i = 0; i < 23; i++){
      infile >> tmp >> Activities_Ext[i] >> Activities_Ext_Err[i]; 
    }

    for(int i = 0; i < 17; i++){
      infile >> tmp >> Activities_Rad[i] >> Activities_Rad_Err[i]; 
    }

    for(int i = 0; i < 9; i++){
      infile >> tmp >> Activities_Int[i] >> Activities_Int_Err[i]; 
    }

    for(int i = 0; i < 2; i++){
      infile >> tmp >> Activities_Sig[i] >> Activities_Sig_Err[i]; 
    }

    for(int i = 0; i < 44; i++){
      infile >> tmp >> AdjustActs[i] >> AdjustActs_Err[i]; 
    }

    infile.close();

  }

}

void writeDenominators(string filename, double *Denominators_Ext, double *Denominators_Rad, double *Denominators_Int, double *Denominators_Sig){

  ofstream outfile;

  outfile.open(filename.c_str());

  if(outfile.is_open()){

    for(int i = 0; i < 21; i++){
      outfile << "Denominators_Ext[" << i << "]= " << Denominators_Ext[i] << endl; 
    }

    for(int i = 0; i < 13; i++){
      outfile << "Denominators_Rad[" << i << "]= " << Denominators_Rad[i] << endl; 
    }

    for(int i = 0; i < 16; i++){
      outfile << "Denominators_Int[" << i << "]= " << Denominators_Int[i] << endl; 
    }

    for(int i = 0; i < 2; i++){
      outfile << "Denominators_Sig[" << i << "]= " << Denominators_Sig[i] << endl; 
    }

    outfile.close();

  }

}

void readDenominators(string filename, double *Denominators_Ext, double *Denominators_Rad, double *Denominators_Int, double *Denominators_Sig){

  ifstream infile;

  infile.open(filename.c_str());

  if(infile.is_open()){
    string tmp;

    for(int i = 0; i < 21; i++){
      infile >> tmp >> Denominators_Ext[i]; 
    }

    for(int i = 0; i < 13; i++){
      infile >> tmp >> Denominators_Rad[i]; 
    }

    for(int i = 0; i < 16; i++){
      infile >> tmp >> Denominators_Int[i]; 
    }

    for(int i = 0; i < 2; i++){
      infile >> tmp >> Denominators_Sig[i]; 
    }

    infile.close();

  }

}

void writeCovMatrix(string filename, Double_t CovMatrix[][44]){

  ofstream outfile;

  outfile.open(filename.c_str());

  if(outfile.is_open()){

    for(int i = 0; i < 44; i++){
      for(int j = 0; j < 44; j++){
	if(CovMatrix[i][j] == CovMatrix[i][j]){
	  outfile << CovMatrix[i][j] << endl;
	} else {
	  outfile << 100000000 << endl;
	}
      }
    }
    outfile.close();
  }

}

void readCovMatrix(string filename, Double_t CovMatrix[][44]){

  ifstream infile;

  infile.open(filename.c_str());

  if(infile.is_open()){

    for(int i = 0; i < 44; i++){
      for(int j = 0; j < 44; j++){
	infile >> CovMatrix[i][j];
      }
    }
    infile.close();
  }

}

void printActivities(double *Activities_Ext, double *Activities_Ext_Err,
		     double *Activities_Rad, double *Activities_Rad_Err,
		     double *Activities_Int, double *Activities_Int_Err,
		     double *Activities_Sig, double *Activities_Sig_Err,
		     double *AdjustActs,     double *AdjustActs_Err){

  cout << "Externals: " << endl;
  cout << "PMT K40              = " << Activities_Ext[0]  << " +/- " << Activities_Ext_Err[0] << endl;	 
  cout << "PMT Bi214            = " << Activities_Ext[1]  << " +/- " << Activities_Ext_Err[1] << endl;	 
  cout << "PMT Tl208            = " << Activities_Ext[2]  << " +/- " << Activities_Ext_Err[2] << endl;	 
  cout << "PMT Ac228            = " << Activities_Ext[3]  << " +/- " << Activities_Ext_Err[3] << endl;	 
  cout << "Mu Metal Co60        = " << Activities_Ext[4]  << " +/- " << Activities_Ext_Err[4] << endl;	 
  cout << "Steel Frame K40      = " << Activities_Ext[5]  << " +/- " << Activities_Ext_Err[5] << endl;	 
  cout << "Steel Frame Bi214    = " << Activities_Ext[6]  << " +/- " << Activities_Ext_Err[6] << endl;	 
  cout << "Steel Frame Tl208    = " << Activities_Ext[7]  << " +/- " << Activities_Ext_Err[7] << endl;	 
  cout << "Steel Frame Ac228    = " << Activities_Ext[8]  << " +/- " << Activities_Ext_Err[8] << endl;	 
  cout << "Steel Frame Co60     = " << Activities_Ext[9]  << " +/- " << Activities_Ext_Err[9] << endl;	 
  cout << "Cu Petals Co60       = " << Activities_Ext[10] << " +/- " << Activities_Ext_Err[10] << endl;
  cout << "Cu Tower Co60        = " << Activities_Ext[11] << " +/- " << Activities_Ext_Err[11] << endl;
  cout << "Fe Shield Bi214      = " << Activities_Ext[12] << " +/- " << Activities_Ext_Err[12] << endl;
  cout << "Fe Shield Tl208      = " << Activities_Ext[13] << " +/- " << Activities_Ext_Err[13] << endl;
  cout << "Fe Shield Ac228      = " << Activities_Ext[14] << " +/- " << Activities_Ext_Err[14] << endl;
  cout << "Scint Inn K40        = " << Activities_Ext[15] << " +/- " << Activities_Ext_Err[15] << endl;
  cout << "Scint Out K40        = " << Activities_Ext[16] << " +/- " << Activities_Ext_Err[16] << endl;
  cout << "Scint Pet K40        = " << Activities_Ext[17] << " +/- " << Activities_Ext_Err[17] << endl;
  cout << "SScin Pa234m         = " << Activities_Ext[18] << " +/- " << Activities_Ext_Err[18] << endl;
  cout << "Mu Metal g1000 P1    = " << Activities_Ext[19] << " +/- " << Activities_Ext_Err[19] << endl;
  cout << "Mu Metal g1000 P2    = " << Activities_Ext[20] << " +/- " << Activities_Ext_Err[20] << endl;
  cout << "Neutrons P1          = " << Activities_Ext[21] << " +/- " << Activities_Ext_Err[21] << endl;
  cout << "Neturons P2          = " << Activities_Ext[22] << " +/- " << Activities_Ext_Err[22] << endl << endl;


  cout << "Radon: " << endl;
  cout << "SWire Bi214 P1       = " << 1000*Activities_Rad[0] << " +/- " << 1000*Activities_Rad_Err[0] << endl;	 
  cout << "SWire Tl208 P1       = " << 1000*Activities_Rad[1] << " +/- " << 1000*Activities_Rad_Err[1] << endl;	 
  cout << "SFoil Bi214 In P1    = " << 1000*Activities_Rad[2] << " +/- " << 1000*Activities_Rad_Err[2] << endl;	 
  cout << "SFoil Bi214 Out P1   = " << 1000*Activities_Rad[3] << " +/- " << 1000*Activities_Rad_Err[3] << endl;	 
  cout << "SWire Bi214 P2       = " << 1000*Activities_Rad[4] << " +/- " << 1000*Activities_Rad_Err[4] << endl;	 
  cout << "SWire Tl208 P2       = " << 1000*Activities_Rad[5] << " +/- " << 1000*Activities_Rad_Err[5] << endl;	 
  cout << "SFoil Bi214 In  P2   = " << 1000*Activities_Rad[6] << " +/- " << 1000*Activities_Rad_Err[6] << endl;	 
  cout << "SFoil Bi214 Out P2   = " << 1000*Activities_Rad[7] << " +/- " << 1000*Activities_Rad_Err[7] << endl;	 
  cout << "SWire Bi210          = " << 1000*Activities_Rad[8] << " +/- " << 1000*Activities_Rad_Err[8] << endl;	 
  cout << "SFoil SeNew Bi210    = " << 1000*Activities_Rad[9] << " +/- " << 1000*Activities_Rad_Err[9] << endl;
  cout << "SFoil SeOld Bi210    = " << 1000*Activities_Rad[10]<< " +/- " << 1000*Activities_Rad_Err[10]<< endl;
  cout << "SFoil Strip Bi210    = " << 1000*Activities_Rad[11]<< " +/- " << 1000*Activities_Rad_Err[11]<< endl;
  cout << "SScin Bi214 P1       = " << 1000*Activities_Rad[12]<< " +/- " << 1000*Activities_Rad_Err[12]<< endl;
  cout << "SScin Bi214 P2       = " << 1000*Activities_Rad[13]<< " +/- " << 1000*Activities_Rad_Err[13]<< endl;
  cout << "SScin Bi210          = " << 1000*Activities_Rad[14]<< " +/- " << 1000*Activities_Rad_Err[14]<< endl;
  cout << "Air Bi214 P1         = " << 1000*Activities_Rad[15]<< " +/- " << 1000*Activities_Rad_Err[15]<< endl;
  cout << "Air Tl208 P1         = " << 1000*Activities_Rad[16]<< " +/- " << 1000*Activities_Rad_Err[16]<< endl;
  cout << "Radon P1/P2          = " << AdjustActs[3]          << " +/- " << AdjustActs_Err[3] << endl << endl;

  cout << "Internals: " << endl;
  cout << "SeNew Bi214          = " << 1000*Activities_Int[0] << " +/- " << 1000*Activities_Int_Err[0] << endl;
  cout << "SeOld Bi214          = " << 1000*Activities_Int[1] << " +/- " << 1000*Activities_Int_Err[1] << endl;
  cout << "Mylar Bi214          = " << 1000*Activities_Int[2] << " +/- " << 1000*Activities_Int_Err[2] << endl;
  cout << "SeNew Tl208          = " << 1000*Activities_Int[3] << " +/- " << 1000*Activities_Int_Err[3] << endl;
  cout << "SeOld Tl208          = " << 1000*Activities_Int[4] << " +/- " << 1000*Activities_Int_Err[4] << endl;
  cout << "SeNew Pa234m         = " << 1000*Activities_Int[5] << " +/- " << 1000*Activities_Int_Err[5] << endl;
  cout << "SeOld Pa234m         = " << 1000*Activities_Int[6] << " +/- " << 1000*Activities_Int_Err[6] << endl;
  cout << "SeNew K40            = " << 1000*Activities_Int[7] << " +/- " << 1000*Activities_Int_Err[7] << endl;
  cout << "SeOld K40            = " << 1000*Activities_Int[8] << " +/- " << 1000*Activities_Int_Err[8] << endl << endl;

  cout << "Signal: " << endl;
  Double_t Halflife_2b2n     = (log(2)/(86400.0*365.25))/(Activities_Sig[0]*82.0/(6.022e4*932.4));
  Double_t Halflife_2b2n_Err = Halflife_2b2n*Activities_Sig_Err[0]/Activities_Sig[0];
  cout << "2b2n (Half-life)     = " << Halflife_2b2n << " +/- " << Halflife_2b2n_Err << " x 10^19 yrs" << endl;
  Double_t Halflife_2b0n     = (log(2)/(86400.0*365.25))/(Activities_Sig[1]*82.0/(6.022*932.4));
  Double_t Halflife_2b0n_Err = Halflife_2b0n*Activities_Sig_Err[1]/Activities_Sig[1];
  cout << "2b0n (Half-life)     = " << Halflife_2b0n << " +/- " << Halflife_2b0n_Err << " x 10^23 yrs" << endl;

}
