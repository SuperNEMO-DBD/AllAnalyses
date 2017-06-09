#ifndef LIMITCALCULATIONFUNCTIONS_H_
#define LIMITCALCULATIONFUNCTIONS_H_

#include <map>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#include <TH1D.h>
#include "TLimit.h"
#include "TLimitDataSource.h"
#include "TConfidenceLevel.h"

#include "TVectorD.h"
using namespace std;

void print_limit_results(double s, TConfidenceLevel* cl, std::ostream& os = std::cout) {
  os << " - signal = " << fixed << s
     << " -- CLs = " << std::setprecision(6) << cl->CLs()
     << " -- CLb = " << std::setprecision(6) << cl->CLb()
     << " -- CLsb = " << std::setprecision(6) << cl->CLsb()
     <<endl;
} 

void print_exp_limit_results(double s, TConfidenceLevel* cl, std::ostream& os = std::cout) {
  os << " - signal = " << fixed << s
     << " -- <CLs> = " << std::setprecision(6) << cl->GetExpectedCLs_b()
     << " -- <CLb> = " << std::setprecision(6) << cl->GetExpectedCLb_b()
     << " -- <CLsb> = " << std::setprecision(6) << cl->GetExpectedCLsb_b()
     <<endl;
} 

//----------------------------------------------------------------------------------------------------

double Expected_Limit_Sig_Evts(double ConfidenceLevel, TH1D* h_signal, TH1D* h_background, TH1D* h_data) {

  // Number of events is given by (this_val * h_signal->Integral)

  double low_bound = 0.1/h_signal->Integral();
  double high_bound = 1000.0/h_signal->Integral();

  TH1D* null_hyp_signal = (TH1D*) h_signal->Clone("null_hyp_signal"); null_hyp_signal->Scale(low_bound);
  TH1D* disc_hyp_signal = (TH1D*) h_signal->Clone("disc_hyp_signal"); disc_hyp_signal->Scale(high_bound);

  TLimitDataSource* mydatasource = new TLimitDataSource(null_hyp_signal, h_background, h_data);
  TConfidenceLevel* myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
  double low_bound_cl = myconfidence->CLs();
  delete mydatasource;

  mydatasource = new TLimitDataSource(disc_hyp_signal, h_background, h_data);
  myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
  double high_bound_cl = myconfidence->CLs();
  delete mydatasource;

  double accuracy = 0.01;
  double this_cl = 0;
  double this_val = 0;

  while  (fabs(high_bound - low_bound) / h_signal->Integral() > accuracy) {
    // bisection
    this_val = low_bound+(high_bound - low_bound)/3;

    TH1D* this_signal = (TH1D*) h_signal->Clone("test_signal"); this_signal->Scale(this_val);
    mydatasource = new TLimitDataSource(this_signal, h_background, h_data);
    myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
    this_cl = myconfidence->GetExpectedCLs_b();

    print_exp_limit_results(this_signal->Integral(), myconfidence);

    if (this_cl > ConfidenceLevel) {
      low_bound = this_val;
      low_bound_cl = this_cl;
    } else {
      high_bound = this_val;
      high_bound_cl = this_cl;
    }

    delete mydatasource;
    delete this_signal;
    delete myconfidence;
  }

  delete null_hyp_signal;
  delete disc_hyp_signal;

  return h_signal->Integral() * this_val;
}

double Limit_Sig_Evts(double ConfidenceLevel, TH1D* h_signal, TH1D* h_background, TH1D* h_data) {

  // Number of events is given by (this_val * h_signal->Integral)

  double low_bound = 0.1/h_signal->Integral();
  double high_bound = 1000.0/h_signal->Integral();

  TH1D* null_hyp_signal = (TH1D*) h_signal->Clone("null_hyp_signal"); null_hyp_signal->Scale(low_bound);
  TH1D* disc_hyp_signal = (TH1D*) h_signal->Clone("disc_hyp_signal"); disc_hyp_signal->Scale(high_bound);

  TLimitDataSource* mydatasource = new TLimitDataSource(null_hyp_signal, h_background, h_data);
  TConfidenceLevel* myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
  double low_bound_cl = myconfidence->CLs();
  delete mydatasource;

  mydatasource = new TLimitDataSource(disc_hyp_signal, h_background, h_data);
  myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
  double high_bound_cl = myconfidence->CLs();
  delete mydatasource;

  double accuracy = 0.001;
  double this_cl = 0;
  double this_val = 0;

  while  (fabs(high_bound - low_bound) / h_signal->Integral() > accuracy) {
    // bisection
    this_val = low_bound+(high_bound - low_bound)/3;

    TH1D* this_signal = (TH1D*) h_signal->Clone("test_signal"); this_signal->Scale(this_val);
    mydatasource = new TLimitDataSource(this_signal, h_background, h_data);
    myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
    this_cl = myconfidence->CLs();

    print_limit_results(this_signal->Integral(), myconfidence);

    if (this_cl > ConfidenceLevel) {
      low_bound = this_val;
      low_bound_cl = this_cl;
    } else {
      high_bound = this_val;
      high_bound_cl = this_cl;
    }

    delete mydatasource;
    delete this_signal;
    delete myconfidence;
  }

  delete null_hyp_signal;
  delete disc_hyp_signal;

  return h_signal->Integral() * this_val;
}

double Expected_Limit_Sig_Evts(double ConfidenceLevel, TH1D* h_signal, TH1D* h_background, TH1D* h_data, TVectorD s_syst, TVectorD b_syst, TObjArray* names){

  // Number of events is given by (this_val * h_signal->Integral)

  double low_bound = 0.001/h_signal->Integral();
  double high_bound = 1000.0/h_signal->Integral();

  TH1D* null_hyp_signal = (TH1D*) h_signal->Clone("null_hyp_signal"); null_hyp_signal->Scale(low_bound);
  TH1D* disc_hyp_signal = (TH1D*) h_signal->Clone("disc_hyp_signal"); disc_hyp_signal->Scale(high_bound);

  TLimitDataSource* mydatasource = new TLimitDataSource(null_hyp_signal, h_background, h_data, &s_syst, &b_syst, names);
  TConfidenceLevel* myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
  double low_bound_cl = myconfidence->CLs();
  delete mydatasource;

  mydatasource = new TLimitDataSource(disc_hyp_signal, h_background, h_data, &s_syst, &b_syst, names);
  myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
  double high_bound_cl = myconfidence->CLs();
  delete mydatasource;

  double accuracy = 0.01;
  double this_cl = 0;
  double this_val = 0;

  while  (fabs(high_bound - low_bound) / h_signal->Integral() > accuracy) {
    // bisection
    this_val = low_bound+(high_bound - low_bound)/3;

    TH1D* this_signal = (TH1D*) h_signal->Clone("test_signal"); this_signal->Scale(this_val);
    mydatasource = new TLimitDataSource(this_signal, h_background, h_data, &s_syst, &b_syst, names);
    myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
    this_cl = myconfidence->GetExpectedCLs_b();

    print_exp_limit_results(this_signal->Integral(), myconfidence);

    if (this_cl > ConfidenceLevel) {
      low_bound = this_val;
      low_bound_cl = this_cl;
    } else {
      high_bound = this_val;
      high_bound_cl = this_cl;
    }

    delete mydatasource;
    delete this_signal;
    delete myconfidence;
  }

  delete null_hyp_signal;
  delete disc_hyp_signal;

  return h_signal->Integral() * this_val;
}


double Limit_Sig_Evts(double ConfidenceLevel, TH1D* h_signal, TH1D* h_background, TH1D* h_data, TVectorD s_syst, TVectorD b_syst, TObjArray* names) {

  // Number of events is given by (this_val * h_signal->Integral)

  double low_bound = 0.001/h_signal->Integral();
  double high_bound = 1000.0/h_signal->Integral();

  TH1D* null_hyp_signal = (TH1D*) h_signal->Clone("null_hyp_signal"); null_hyp_signal->Scale(low_bound);
  TH1D* disc_hyp_signal = (TH1D*) h_signal->Clone("disc_hyp_signal"); disc_hyp_signal->Scale(high_bound);

  TLimitDataSource* mydatasource = new TLimitDataSource(null_hyp_signal, h_background, h_data, &s_syst, &b_syst, names);
  TConfidenceLevel* myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
  double low_bound_cl = myconfidence->CLs();
  delete mydatasource;

  mydatasource = new TLimitDataSource(disc_hyp_signal, h_background, h_data, &s_syst, &b_syst, names);
  myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
  double high_bound_cl = myconfidence->CLs();
  delete mydatasource;

  double accuracy = 0.001;
  double this_cl = 0;
  double this_val = 0;

  while  (fabs(high_bound - low_bound) / h_signal->Integral() > accuracy) {
    // bisection
    this_val = low_bound+(high_bound - low_bound)/3;

    TH1D* this_signal = (TH1D*) h_signal->Clone("test_signal"); this_signal->Scale(this_val);
    mydatasource = new TLimitDataSource(this_signal, h_background, h_data, &s_syst, &b_syst, names);
    myconfidence = TLimit::ComputeLimit(mydatasource, 50000);
    this_cl = myconfidence->CLs();

    print_limit_results(this_signal->Integral(), myconfidence);

    if (this_cl > ConfidenceLevel) {
      low_bound = this_val;
      low_bound_cl = this_cl;
    } else {
      high_bound = this_val;
      high_bound_cl = this_cl;
    }

    delete mydatasource;
    delete this_signal;
    delete myconfidence;
  }

  delete null_hyp_signal;
  delete disc_hyp_signal;

  return h_signal->Integral() * this_val;
}

#endif
