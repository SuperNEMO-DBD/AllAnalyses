#ifndef MULTIHISTOGRAM_HPP
#define MULTIHISTOGRAM_HPP


#include "HistogramGraphData.hpp"
#include "TH1Data.hpp"


#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <limits>


//#include <TROOT.h>
#include <Rtypes.h>
#include <TH1.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TFile.h>



// Globally accessable functions and variable to make initialzation of
// histogram easier

const Float_t GLOBAL_AXIS_TITLE_SIZE{0.04};
const Float_t GLOBAL_AXIS_LABEL_SIZE{0.03};

void
SetTH1DefaultXY(TH1* const histogram,
                const std::string& x_title, const std::string& y_title,
                const Bool_t sum_w2_enable = false);



//
// MultiHistogramStateMode
//
// Default: Default floating point histogram y-axis
// Log: Logarithmic floating point histogram y-axis. Round histogram axis min/max to powers of 10
// Integer: (Not fully implemented) Round histogram axis to integers / multiples of 10, 20, 50, 100 (?)
//
enum class MultiHistogramStateMode
{
    DEFAULT,
    INTEGER,
    LOG,
};


//
// MultiHistogramState
//
// Class stores all state variables for MultiHistogram class. When drawing multiple histograms (TH1* object)
// some state variables should be universal. _error_enable: Do 1 or more histograms have errors enabled?
// Typically all do or none do? If this flag is set to true, then the autoscale functions take into account
// the errorbars of each boin on the histogram. Else the errors are ignored.
//
class MultiHistogramState
{


public:

    bool _error_enable; // TODO: Get/Set methods for these variables
    bool _auto_y_min; // set true if autoscale functions should automatically set the minimum / maximum of the histogram y-axis
    bool _auto_y_max;
    Float_t _y_min; // Actual values for min/max returned by autoscale functions
    Float_t _y_max;

    // changes the way autohistoscale() rounds to nearest [...]
    
private:
    
    public: MultiHistogramStateMode _state_mode; // TODO: Kept as public for the time being however there are Get/Set methods for this
    //private: Int_t _line_width;
    

public:

    MultiHistogramState()
        : _error_enable{false} // TODO
        , _auto_y_min{true}
        , _auto_y_max{true}
        , _y_min{0.0}
        , _y_max{0.0}
        , _state_mode{MultiHistogramStateMode::DEFAULT}
    {
    }
    
    MultiHistogramState(const Float_t y_min, const Float_t y_max)
        : _error_enable{false} // TODO
        , _auto_y_min{false}
        , _auto_y_max{false}
        , _y_min{y_min}
        , _y_max{y_max}
    {
    } 

    // This constructor generally used for "logmode"
    // ie; when canvas is set to log-y mode, a value greater than
    // 0.0 can be manually set as the minimum
    MultiHistogramState(const Float_t y_min)
        : _error_enable{false} // TODO
        , _auto_y_min{false}
        , _auto_y_max{true}
        , _y_min{y_min}
        , _y_max{0.0}
    {
    }
    
    void SetStateMode(MultiHistogramStateMode state)
    {
        _state_mode = state;
    }

    MultiHistogramStateMode GetStateMode() const
    {
        return _state_mode;
    }
    
};



//
// MultiHistogram
//


// TODO
// each of these objects should have its own output directory
// as a variable set in the constructor
class MultiHistogram
{

public:

    // *** THESE POINTERS ARE ALLOCATED ELSEWHERE DO NOT DELETE THEM ***
    // TODO May need to change this later
private:

    // Maps documentation:
    //
    // It is not convenient to store multiple TH1* objects in a STL container and
    // refer to them only via their address in the contianer. (Index) Instead, 2
    // maps are provided. One convert numerical UIDs (names) to a TH1 pointer
    // which stores the address of the allocated TH1* object. The other map converts
    // std::string names (human readable names) to the corresponding numerical UID
    // of the histogram.
    // If one wishes to address histograms by index, then the UID should be set
    // sequentially, with the same values as would correspond to the index.
    // 
    // Summary: The maps convert names in the following manner:
    // std::string -> UID (size_t) -> TH1Data pointer (memory address)
    //
    // Example:
    // "Neutron Background" -> 0 -> 0xXXXXXXXX (some dynamic memory address)
    //

    // container for histograms (in TH1Data structure)
    std::vector<TH1Data*> _histogram;
    
    // map to convert numerical names to pointers to TH1Data objects
    std::map<size_t, TH1Data*> _histogram_map_numeric;
    
    // no longer used!
    //std::map<std::string, TH1Data*> _histogram_map_string;
    
    // map to convert numerical names to string names
    // this may acutally not be required!
    // because you never need to convert in this direction!
    //std::map<size_t, std::string> _name_map_numeric_string;
    
    // map to convert string names to numerical names
    std::map<std::string, size_t> _name_map_string_numeric;
        // the maps are used to refer to a histogram by name (string) or index (size_t)
        // for example, strings may be "signal" or "background"
        // for several signals and background channels which are uid'd by a numerical value,
        // then use the numerical mapping
    
    //std::pair<TH1*, std::string*>> _histogram;
    
    // This pointer is managed by this class
    TCanvas *_canvas;

    MultiHistogramState _state; // Essentially a class which wraps a few global variables for this class together
    Bool_t _line_color_auto; // could go in MultiHistogramState (but at the moment this class contains only autohistoscale variables)
    
    Int_t _line_width;
    Bool_t _line_width_enable;
    
    std::string _output_dir;

    
    // TODO : void Fill function(s) (one with weight)
    
private:

    // private functions
    
    /*
    friend
    void swap(MultiHistogram& first, MultiHistogram& second)
    {
        using std::swap;
        
        swap(first._histogram, second._histogram);
        swap(first._canvas, second._canvas);
        swap(first._state, second._state);
    }
    */
    
    // TODO: Autohistoscale
    
    // TODO: it would be better if these worked like:
    // -> as they do now for histograms with floating point content (weighted?)
    //    where 10 % / 20 % is added as a buffer space for the upper / lower limit
    // -> differently in the following way for logarithmic and integer content
    //    histograms
    // -> for integer content, the nearest or ceil() (next) integer of the largest
    //    bin content + 10 % / 20 % should be chosen as the upper limit
    //    (or maybe it should go in 5's / 10's or whatever
    // -> for logarithmic histograms, the next power of 10 should be chosen as the
    //    upper limit
    
    // This will work because GetMaximum is called by autohistoscale before SetRangeUser
    // SetRangeUser changes the value returned by GetMaximum and GetMinimum in TH1* objects
    Double_t autohistoscale_get_maximum() const
    {
        
        // Get maximum (basic autohistoscale)
        std::vector<TH1Data*>::const_iterator it = _histogram.cbegin();
        Double_t max = 1.0; // does not blow up for log (default value)
        
        // If at least 1 histogram exists, then get value from this histogram
        // (replace default value), if more than 1 histogram exists, get the
        // maximum of all histograms
        if(it != _histogram.cend())
        {
            max = (*it)->Histogram()->GetMaximum();
            ++ it;
        }
        for(; it != _histogram.cend(); ++ it)
        {
            if((*it)->Histogram()->GetMaximum() > max)
                max = (*it)->Histogram()->GetMaximum();
        }
        
        
        
        return max;
    }
    
    // This will work because GetMinimum is called by autohistoscale before SetRangeUser
    // SetRangeUser changes the value returned by GetMaximum and GetMinimum in TH1* objects
    Double_t autohistoscale_get_minimum() const
    {
        
        // Get minimum (basic autohistoscale)
        std::vector<TH1Data*>::const_iterator it = _histogram.cbegin();
        Double_t min = 0.1; // does not blow up for log (default value)
        
        // If at least 1 histogram exists, then get value from this histogram
        // (replace default value), if more than 1 histogram exists, get the
        // minimum of all histograms
        if(it != _histogram.cend())
        {
            min = (*it)->Histogram()->GetMinimum();
            ++ it;
        }
        for(; it != _histogram.cend(); ++ it)
        {
            if((*it)->Histogram()->GetMinimum() < min)
                min = (*it)->Histogram()->GetMinimum();
        }
        
        
        return min;
    }

    // This will work because GetMinimum is called by autohistoscale before SetRangeUser
    // SetRangeUser changes the value returned by GetMaximum and GetMinimum in TH1* objects
    
    // This version of the get_minimum function ignores all empty bins
    // Function called, GetMinManualIgnoreEmpty, returns the minimum, while ignoring any
    // histogram bins which have 0.0 or less content
    // This is used for scaling logarithmic histograms.
    // GetMinManualIgnoreEmpty returns 0.1 (default value) if there are no > 0.0 minimum bins
    // If there is a minimum bin which has content greater than 0.1, then 0.1 is still
    // returned as a minium value. This is because most histograms even with large numbers of events
    // typically look better if the minimum is fixed at 0.1.
    // This can be changed by altering the code.
    // TODO: Add a flag to fix minimum at 0.1 (this is for a later version release of this code.)
    Double_t autohistoscale_get_minimum_ignore_empty() const
    {
        
        // Get minimum (basic autohistoscale)
        std::vector<TH1Data*>::const_iterator it = _histogram.cbegin();
        Double_t min = 0.1; // does not blow up for log
        
        // If at least 1 histogram exists, then get value from this histogram
        // (replace default value), if more than 1 histogram exists, get the
        // minimum of all histograms
        if(it != _histogram.cend())
        {
            Double_t tempmin; // will be set to 0.1 and then non-zero minimum is found (value will be > 0.0)
            GetMinManualIgnoreEmpty(tempmin, (*it)->Histogram());
            if(tempmin > 0)
               min = tempmin;
            
            ++ it;
        }
        for(; it != _histogram.cend(); ++ it)
        {
            Double_t tempmin;
            GetMinManualIgnoreEmpty(tempmin, (*it)->Histogram());
            if(tempmin > 0)
            {
                if(tempmin < min)
                {
                    min = tempmin;
                }
            }
        }
        
        
        return min;
    }

    // This will work because GetMinimum is called by autohistoscale before SetRangeUser
    // SetRangeUser changes the value returned by GetMaximum and GetMinimum in TH1* objects
    
    // This version of the get_maximum function ignores all empty bins
    // Function called, GetMaxManualIgnoreEmpty, returns the minimum, while ignoring any
    // histogram bins which have 0.0 or less content
    // This is used for scaling logarithmic histograms.
    // GetMaxManualIgnoreEmpty returns 1.0 (default value) if there are no > 0.0 maximum bins
    // If there is a maximum bin which has content greater than 1.0, then 1.0 is still
    // returned as a maxium value. This is because most histograms even with small numbers of events
    // typically look better if the maximum is fixed at 1.0.
    // This can be changed by altering the code.
    // TODO: Add a flag to fix minimum at 1.0 (this is for a later version release of this code.)
    Double_t autohistoscale_get_maximum_ignore_empty() const
    {
        
        // Get minimum (basic autohistoscale)
        std::vector<TH1Data*>::const_iterator it = _histogram.cbegin();
        Double_t max = 1.0; // does not blow up for log
        
        
        // If at least 1 histogram exists, then get value from this histogram
        if(it != _histogram.cend())
        {
            //min = (*it).first->GetMinimum();
            Double_t tempmax; // will be set to 0.1 and then non-zero minimum is found (value will be > 0.0)
            GetMaxManualIgnoreEmpty(tempmax, (*it)->Histogram());
            //if(it->Histogram()->GetMinimum() > 0)
            if(tempmax > 0)
               max = tempmax;
               //min = it->Histogram()->GetMinimum();
            
            ++ it;
        }
        for(; it != _histogram.cend(); ++ it)
        {
            //if((*it).first->GetMinimum() < min)
            //if(it->Histogram()->GetMinimum() > 0.0)
            Double_t tempmax;
            GetMaxManualIgnoreEmpty(tempmax, (*it)->Histogram());
            if(tempmax > 0)
            {
                //if(it->Histogram()->GetMinimum() < min)
                if(tempmax > max)
                {
                    //min = (*it).first->GetMinimum();
                    //min = it->Histogram()->GetMinimum();
                    max = tempmax;
                }
            }
        }
        
        
        return max;
    }
    
    // Note: A blank histogram with no events will have the min/max set to 0.1/1.0, and therefore
    // a canvas can be drawn if a histogram is blank and contains no data


    // Log histogram round up / down to next / previous power of 10
    Double_t ceil_pow_10(const Double_t input) const  
    {
        return std::pow(10.0, std::ceil(std::log10(input)));    
    }
    
    Double_t floor_pow_10(const Double_t input) const
    {
        return std::pow(10.0, std::floor(std::log10(input)));
    }
    

    void GetMinManual(Double_t &hmin, const TH1* histogram) const
    {
        Double_t hhmin{0.0};
        
        //for(size_t ix = 1; ix <= histogram->GetNbinsX(); ++ ix)
        //{
        //    hhmin = std::min(hhmin, histogram->GetBinContent(ix));
        //}
        
        // this code does the same as the above loop
        hhmin = histogram->GetBinContent(histogram->GetMinimumBin());
        
        hmin = hhmin;
        
        return;
    }

    void GetMaxManual(Double_t& hmax, const TH1* histogram) const
    {
        Double_t hhmax{0.0};
        
        //for(size_t ix = 1; ix <= histogram->GetNbinsX(); ++ ix)
        //{
        //    hhmax = std::max(hhmax, histogram->GetBinContent(ix));
        //}
        
        // this code does the same as the above loop
        hhmax = histogram->GetBinContent(histogram->GetMaximumBin());
        
        hmax = hhmax;
        
        return;
    }
    
    
    // does not blow up for log!
    void GetMinManualIgnoreEmpty(Double_t &hmin, const TH1* histogram) const
    {
        Double_t hhmin{0.1};
        
        // require a loop here because GetMinimumBin may return a bin with <= 0.0 content
        for(size_t ix = 1; ix <= histogram->GetNbinsX(); ++ ix)
        {            
            // avoid 0.0 - prevent log blowing up
            if(histogram->GetBinContent(ix) > 0.0)
                hhmin = std::min(hhmin, histogram->GetBinContent(ix));
        }
        
        // cant remember why this code was here? might need to re-enable it some time?
        // avoid problems where hhmin > hhmax
        //if(hhmax < hhmin)
        //    hhmin = hhmax;
    
        hmin = hhmin;
    
        return;
    }
    
    // TODO: This will not work well for histograms where all data is between
    // 0.1 and 1.0 but very close, eg spread of 10e-3 or less
    // but in such cases, you probably don't want to plot a logarithmic histogram
    // you might need to write your own function and extend this class if you
    // are trying to plot data with an unusual range of values, for example, very large
    // numbers, very small numbers, or numbers where the spread is comparatively small
    // compared to 1.0, or small compared to the minimum / maximum value
    // ranges which will not work well:
    // 1.0e-08 to 1.0e-05 (spread small compared to 1.0, minimum will be 1.0e-8, maximum "stuck" at 1.0)
    // 1.0e+05 to 1.0e+08 (minimum value >> 1.0, minimum "stuck" at 1.0)
    // 0.350 to 0.351 (spread very small compared to 1.0 - 0.1, both ends of range "stuck")
    // In these cases, root probably doesn't do a good job of drawing the axis ticks and labels anyway
    // hence one should save the output as a .C file and edit the drawing manually, then re-run the .C
    // macro with the root CINT c++ interpreter.
    // This class is very useful for making the job of drawing many histograms on the same canvas easier
    // it doesn't always produce a publication quality output, but it is significantly quicker to
    // get there compared to doing everything manually by loading data with a .C macro written manualy
    void GetMaxManualIgnoreEmpty(Double_t& hmax, const TH1* histogram) const
    {
        Double_t hhmax{1.0};
        
        // require a loop here because GetMinimumBin may return a bin with <= 0.0 content
        for(size_t ix = 1; ix <= histogram->GetNbinsX(); ++ ix)
        {            
            // avoid 0.0 - prevent log blowing up
            if(histogram->GetBinContent(ix) > 0.0)
                hhmax = std::max(hhmax, histogram->GetBinContent(ix));
        }
        
        // cant remember why this code was here? might need to re-enable it some time?
        // avoid problems where hhmin > hhmax
        //if(hhmax < hhmin)
        //    hhmin = hhmax;
    
        hmax = hhmax;
    
        return;
    }

    // return both the min and max
    void GetMinMaxManual(Double_t &hmin, Double_t& hmax, const TH1* histogram) const
    {
        Double_t hhmin{0.0};
        Double_t hhmax{0.0};
        
        //for(size_t ix = 1; ix <= histogram->GetNbinsX(); ++ ix)
        //{
        //    hhmin = std::min(hhmin, histogram->GetBinContent(ix));
        //    hhmax = std::max(hhmax, histogram->GetBinContent(ix));
        //}
        
        // code does same as above loop
        hhmin = histogram->GetBinContent(histogram->GetMinimumBin());
        hhmax = histogram->GetBinContent(histogram->GetMaximumBin());
        
        hmin = hhmin;
        hmax = hhmax;
        
        return;
    }
    
    // does not blow up for log!
    void GetMinMaxManualIgnoreEmptyMin(Double_t &hmin, Double_t& hmax, const TH1* histogram) const
    {
        Double_t hhmin{0.1};
        Double_t hhmax{0.0};
        
        // does the same as the commented line of code in the below loop
        hhmax = histogram->GetBinContent(histogram->GetMaximumBin());
        
        // require a loop here because GetMinimumBin may return a bin with <= 0.0 content
        for(size_t ix = 1; ix <= histogram->GetNbinsX(); ++ ix)
        {
            //hhmax = std::max(hhmax, histogram->GetBinContent(ix));
            
            // avoid 0.0 - prevent log blowing up
            if(histogram->GetBinContent(ix) > 0.0)
                hhmin = std::min(hhmin, histogram->GetBinContent(ix));
        }
        
        // avoid problems where hhmin > hhmax
        // problem is now histogram has no range?
        // perhaps this should be changed to swap hhmin and hhmax or
        // return default values?
        // this can happen if 
        if(hhmax < hhmin)
            hhmin = hhmax;
            
        hmin = hhmin;
        hmax = hhmax;
        
        return;
    }


    // private autohistoscale() function
    // sets the histogram y axis scale if either limit is in auto mode
    void autohistoscale()
    {
        // Check state for autohistoscale type function calls
        
        // Check manual limits - minimum
        if(_state._auto_y_min == true)
        {
            if(_state._error_enable == false)
            {
                Double_t temp = autohistoscale_get_minimum();
                
                if(_state._state_mode == MultiHistogramStateMode::DEFAULT) // not much effort was put into this
                {
                    if(temp < 0.0)
                    {
                        _state._y_min = 1.1 * std::abs(temp);
                        _state._y_min = -_state._y_min;
                    }
                    else
                    {
                        _state._y_min = 0.9 * std::abs(temp);
                    }
                }
                else if(_state._state_mode == MultiHistogramStateMode::LOG)
                {
                    // this could be the next order of magnitude LOWER or just return 0.1
                    
                    
                    // This added to prevent log(0.0) error!
                    temp = autohistoscale_get_minimum_ignore_empty();
                    
                    // Do not need this check - temp guaranteed to return > 0
                    if(temp > 0.0)
                    {
                        _state._y_min = floor_pow_10(0.9 * temp); // TODO: this isn't actually the same (ABSOLUTE) margin as for min!
                        // the additional 0.9 ensures exact powers of 10 do not meet the bottom of the graph
                    }
                    else
                    {
                        std::cerr << "ERROR in autohistoscale(), when computing MINIMUM limit: temp <= 0.0" << std::endl;
                    }
                }
                else if(_state._state_mode == MultiHistogramStateMode::INTEGER) // this hasn't been done yet TODO
                {
                    std::cerr << "not implemented" << std::endl;
                }
            }
            else
            {
                std::cerr << "I don't know what to do here..." << std::endl;
            }   
        }
        
        // Check manual limits - maximum
        if(_state._auto_y_max == true)
        {
            if(_state._error_enable == false)
            {
                Double_t temp = autohistoscale_get_maximum();
                
                if(_state._state_mode == MultiHistogramStateMode::DEFAULT) // not much effort was put into this
                {
                    if(temp >= 0.0)
                    {
                        _state._y_max = 1.1 * std::abs(temp);
                    }
                    else
                    {
                        _state._y_max = 0.9 * std::abs(temp);
                        _state._y_max = -_state._y_max;
                    }
                }
                else if(_state._state_mode == MultiHistogramStateMode::LOG)
                {
                
                    // This added to prevent log(0.0) error!
                    temp = autohistoscale_get_maximum_ignore_empty();
                    
                    if(temp > 0.0)
                    {
                        _state._y_max = ceil_pow_10(1.1 * temp);
                        // the additional 1.1 ensures that exact powers of 10 do not meet the top of the graph
                    }
                    else
                    {
                        std::cerr << "ERROR in autohistoscale(), when computing MAXIMUM limit: temp <= 0.0" << std::endl;
                    }
                }
                else if(_state._state_mode == MultiHistogramStateMode::INTEGER) // this hasn't been done yet TODO
                {
                    std::cerr << "not implemented" << std::endl;
                }
            }
            else
            {
                std::cerr << "I don't know what to do here..." << std::endl;
            }
        }
        
        
        // Set histogram limits
        std::vector<TH1Data*>::const_iterator it = _histogram.cbegin();
        for(; it != _histogram.cend(); ++ it)
        {
            (*it)->Histogram()->GetYaxis()->SetRangeUser(_state._y_min, _state._y_max);
            
        }
        //std::cout << "y min = " << _state._y_min << "   y max = " << _state._y_max << std::endl;
        
    }
    

public:

    // public functions

    /*
    MultiHistogram()
        : _canvas{nullptr}
        , _state{MultiHistogramState()}
    {
    }
    */

    MultiHistogram(const std::string &canvas_title, const std::string& output_dir, const MultiHistogramState &state, Bool_t line_color_auto = true)
        : _canvas{nullptr}
        , _state{state}
        , _line_color_auto{line_color_auto}
        , _line_width{1}
        , _line_width_enable{false}
        , _output_dir(output_dir)
    {
        std::string canvas_name(std::string("c_") + canvas_title);
        std::string file_name(output_dir + std::string("/") + canvas_name);
        _canvas = new TCanvas(file_name.c_str(), canvas_title.c_str(), 800, 600);
        //_output_dir = output_dir;
    }
    
    // TODO: don't try to copy / move this object
    // there is 1 pointer to data member (TCanvas)
    // and bad things will happen
    
    MultiHistogram(const MultiHistogram& other) = delete;
    MultiHistogram(MultiHistogram&& other) = delete;
    MultiHistogram& operator=(MultiHistogram other) = delete;
    
    /*
    MultiHistogram(const MultiHistogram& other)
        : _histogram(other._histogram)
        , _canvas{other._canvas}
        , _state{other._state}
    {
    }
    
    MultiHistogram(MultiHistogram&& other)
        : MultiHistogram() // initialize via default constructor, C++11 only
    {
        swap(*this, other);
    }
        
    MultiHistogram& operator=(MultiHistogram other)
    {
        swap(*this, other);
        return *this;
    }
    */
    
    ~MultiHistogram()
    {
        delete _canvas;
        _canvas = nullptr;
        
        //std::vector<TH1Data*>::const_iterator it = _histogram.cbegin();
        std::vector<TH1Data*>::iterator it = _histogram.begin();
        for(; it != _histogram.cend(); ++ it)
        {
            delete (*it);
            (*it) = nullptr;
        }
        
        // The destructor is slightly unusual in that the histogram objects
        // are allocated in the main program and are not deleted here
        // whereas the strings are both allocated and deleted within this class
        //for(std::vector<std::pair<TH1*, std::string*>>::const_iterator it = _histogram.cbegin(); it != _histogram.cend(); ++ it)
        //for(std::vector<TH1Data>::const_iterator it = _histogram.cbegin(); it != _histogram.cend(); ++ it)
        //{
        //    delete (*it).second;
        //}
    }
    

    // write histograms to currently opened / "active"? root file
    void
    Write()
    {
        for(std::vector<TH1Data*>::const_iterator it = _histogram.cbegin(); it != _histogram.cend(); ++ it)
        {
            (*it)->Histogram()->Write();
        }
    }
    
    
    // Draw the histograms to the canvas. Don't do anything dumb like calling this function
    // twice because I have no idea what happens if you do that but probably it's nothing
    // fun
    // Also writes the stats file, which you may wish to change the format of
    
    // TODO: Should SKIP a color (line color) if histogram is not available
    // which i think is what actually happens but then why are the analysis results
    // in RED rather than default BLUE for some graphs?
    // (or has this now changed and I just need to re-run the code?)
    void
    Draw(const std::string &_canvas_output_dir)//, const Long64_t num_entries_input)
    {
    
        // Open log file
        const std::string& output_dir(_canvas_output_dir); //"./output/root/"); // TODO: Need to change output directory
                                                            // note this still works because the _output_dir variable comes inbetween the _canvas_output_dir variable and the canvas_name variable
                                                            // but the code is now a bit illogical - fix this
        std::ofstream statsfile;
        
        _canvas->cd();
        std::string canvas_name{_canvas->GetName()};
        
        std::string statsfilename(output_dir + canvas_name + std::string(".log"));
        statsfile.open(statsfilename.c_str());
        if(!statsfile.is_open())
        {
            //_logfile << "[ ERROR ] : Could not open file " << statsfilename << std::endl;
            std::cerr << "[ ERROR ] : Could not open file " << statsfilename << std::endl;
        }
       
       
        // call autohistoscale
        autohistoscale();
        
        
        // Set histogram limits
        std::vector<TH1Data*>::const_iterator it = _histogram.cbegin();
        for(; it != _histogram.cend(); ++ it)
        {
            
            (*it)->Histogram()->GetXaxis()->SetTitleSize(15);
            (*it)->Histogram()->GetYaxis()->SetTitleSize(15);
            
            (*it)->Histogram()->GetXaxis()->SetTitleFont(43);
            (*it)->Histogram()->GetYaxis()->SetTitleFont(43);
            
            (*it)->Histogram()->GetXaxis()->SetLabelSize(15);
            (*it)->Histogram()->GetYaxis()->SetLabelSize(15);
            
            (*it)->Histogram()->GetXaxis()->SetLabelFont(43);
            (*it)->Histogram()->GetYaxis()->SetLabelFont(43);
            
        }
        
        
        TLegend l(0.7, 0.7, 0.9, 0.9);
        it = _histogram.cbegin();
        //it = _histogram.cend(); // I had this in reverse order at one point can't remember why - all I remember is it didn't work well.
        //-- it;
        for(; it != _histogram.cend(); ++ it)
        //for(; it != _histogram.cbegin() - 1; -- it)
        {
        
            size_t index = std::distance(_histogram.cbegin(), it);
            // don't remember what this was about
            // TODO: Should line width be global (in _state)
            // should line color be individual (in TH1Data)
            // should line color manual color enable/disable be in (TH1Data?)
            // TODO: Enable line widths and colors
            //if(_state.LineColorManual())
            //{
            //    it->Histogram()->SetLineColor(it->GetLineColor());
            //}
            //else
            //{
            //    it->Histogram()->SetLineColor(1 + index);
            //}
            
            
            //
            // Line color
            //
            
            Int_t histogram_color{0};
                // temp color flag
            Bool_t auto_color{false};
                // reduce duplicate code below while keeping logical if statement structure
                // (okay to edit if statements and remove this flag)
            
            if(_line_color_auto)
            {
                auto_color = true;
            }
            else
            {
                if((*it)->GetColorFlagEnable())
                // you can use this flag (individual for each histogram) to over-ride the automatic coloring
                // you should either set the color for each histogram manually or use the automatic color scheme
                // to avoid color conflicts / duplications
                // if you have a very large number of histograms then you will have to set the colors manually
                {
                    histogram_color = (*it)->GetColorFlag();
                }
                else
                {
                    auto_color = true;
                }
            }
            
            // if auto_color mode
            // assumes white background color!
            if(auto_color)
            {
                // Color scheme for up to 4 histograms
                if(std::distance(_histogram.cbegin(), _histogram.cend()) < 4) // should this be <= 4?
                {
                    // default color is blue for a canvas containing a single histogram
                    //it->Histogram()->SetLineColor(4);
                    //histogram_color = 4;
                
                    if(index == 0)
                    {
                        //it->Histogram()->SetLineColor(4); // blue
                        histogram_color = 4;
                    }
                    else if(index == 1)
                    {
                        //it->Histogram()->SetLineColor(2); // red
                        histogram_color = 2;
                    }
                    else if(index == 2)
                    {
                        //it->Histogram()->SetLineColor(3); // green
                        histogram_color = 3;
                    }
                    else if(index == 3)
                    {
                        //it->Histogram()->SetLineColor(1); // black
                        histogram_color = 1;
                    }
                }
                else if(std::distance(_histogram.cbegin(), _histogram.cend()) < 7) // should this be <= 7?
                {
                    // autoset color according to my color ordering when more than 1 histogram on canvas
                
                    // index = 0: blue
                    // index = 1: red
                    // index = 3: green
                    // index = 4: black
                    
                    if(index == 0)
                    {
                        //it->Histogram()->SetLineColor(4); // black
                        histogram_color = 1;
                    }
                    else if(index == 1)
                    {
                        //it->Histogram()->SetLineColor(2); // blue
                        histogram_color = 4;
                    }
                    else if(index == 2)
                    {
                        //it->Histogram()->SetLineColor(3); // red
                        histogram_color = 2;
                    }
                    else if(index == 3)
                    {
                        //it->Histogram()->SetLineColor(1); // green
                        histogram_color = 3;
                    }
                    else if(index == 4)
                        histogram_color = 6; // magenta
                    else if(index == 5)
                        histogram_color = 7; // cyan
                    else if(index == 6)
                        histogram_color = 5; // yellow
                }
                // not really sure how well these color schemes work, you may have to change them
                else if(std::distance(_histogram.cbegin(), _histogram.cend()) < 8) // should this be <= 8?
                {
                    if(index == 0)      histogram_color = 1; // black
                    else if(index == 1) histogram_color = kRed; // red
                    else if(index == 2) histogram_color = kOrange + 7; // -3?; // orange
                    else if(index == 3) histogram_color = kOrange; // -1? // yellow
                    else if(index == 4) histogram_color = kGreen + 2; // different shade? // green (darker)
                    else if(index == 5) histogram_color = kBlue;// - 1; // blue
                    else if(index == 6) histogram_color = kViolet - 6; // violet
                    else if(index == 7) histogram_color = kGray + 1; // grey
                }
                // not really sure how well these color schemes work, you may have to change them
                else if(std::distance(_histogram.cbegin(), _histogram.cend()) < 9) // should this be <= 9?
                {
                    if(index == 0)      histogram_color = 1; // black
                    else if(index == 1) histogram_color = kRed; // red
                    else if(index == 2) histogram_color = kOrange + 7; // -3?; // orange
                    else if(index == 3) histogram_color = kOrange; // -1? // yellow
                    else if(index == 4) histogram_color = kGreen + 2; // different shade? // green (darker)
                    else if(index == 5) histogram_color = kBlue;// - 1; // blue
                    else if(index == 6) histogram_color = kViolet - 6; // violet
                    else if(index == 7) histogram_color = kGray + 1; // grey
                    else if(index == 8) histogram_color = kGray + 3; // [white!]
                }
                // not really sure how well these color schemes work, you may have to change them
                else if(std::distance(_histogram.cbegin(), _histogram.cend()) < 10) // should this be <= 10?
                {
                    if(index == 0)      histogram_color = 1; // black
                    else if(index == 1) histogram_color = kOrange + 4; // brown
                    else if(index == 2) histogram_color = kRed; // red
                    else if(index == 3) histogram_color = kOrange + 7; // -3?; // orange
                    else if(index == 4) histogram_color = kOrange; // -1? // yellow
                    else if(index == 5) histogram_color = kGreen + 2; // different shade? // green (darker)
                    else if(index == 6) histogram_color = kBlue;// - 1; // blue
                    else if(index == 7) histogram_color = kViolet - 6; // violet
                    else if(index == 8) histogram_color = kGray + 1; // grey
                    else if(index == 9) histogram_color = kGray + 3; // [white!]
                }
                else
                {
                    if(index <= 15)
                    {
                        histogram_color = (kBlue - 10) + index;
                    }
                    else
                    {
                        histogram_color = (kViolet - 9) + index;
                    }
                }
                
                // some old code
//                    else if(index == 7)
//                        histogram_color = 8;
//                    else if(index == 8)
//                        histogram_color = 9;
//                    else if(index == 9)
//                        histogram_color = 12;
//                    else if(index == 10)
//                        histogram_color = 14;
//                    else if(index == 11)
//                        histogram_color = 16;
//                    else if(index == 12)
//                        histogram_color = 46;
//                    else
//                    {
//                        //it->Histogram()->SetLineColor(2 + index); // avoid 5=yellow
//                        histogram_color = kRed + index;
//                    }
//                }
            }
            // else color is set by call to GetColorFlag()
            
            (*it)->Histogram()->SetLineColor(histogram_color);
            (*it)->Histogram()->SetMarkerColor(histogram_color);
   
            
            //
            // Line width
            //
            
            // line width works in a simular way, the default is 1, 
            // the over-ride switch can be set in the TH1Data class
            // and hence the width for each histogram can be changed
            // individually
            // there is also on over-ride in this class which changes
            // the default from 1 to some other value
            // the per-histogram over-ride has the highest priority
            
            // TODO: same for line style
            
            Int_t line_width{1}; // default
                                // there is no variable to se the default line width for all graphs
                                // which will be annoying so fix this
            if(_line_width_enable) // used for a global value applied to all histograms, but different from the default value of 1
            {
                line_width = _line_width;
            }
            if((*it)->GetLineWidthOverride()) // per-histogram over-ride
            {
                line_width = (*it)->GetLineWidth();
            }
            (*it)->Histogram()->SetLineWidth(line_width);
            
            
            //it->Histogram()->SetLineWidth(_state.GetLineWidth());
            (*it)->Histogram()->Draw((*it)->GetDrawOPT().c_str());
            l.AddEntry((*it)->Histogram(), (*it)->GetLegendText().c_str());
        }
        
        it = _histogram.cbegin();
        for(; it != _histogram.cend(); ++ it)
        {
            // Print stats to logfile if available
            if(statsfile.is_open())
            {
                
                Double_t hmin{0.0};
                Double_t hmax{0.0};
                
                GetMinMaxManual(hmin, hmax, (*it)->Histogram());
                
                Double_t hmin_ignore_empty{0.1};
                GetMinManualIgnoreEmpty(hmin_ignore_empty, (*it)->Histogram());
                
                //for(size_t ix = 1; ix <= it->Histogram()->GetNbinsX(); ++ it)
                //{
                //    hmax = std::max(hmax, it->Histogram()->GetBinContent(ix));
                //    hmin = std::min(hmin, it->Histogram()->GetBinContent(ix));
                //}
                
                statsfile << std::scientific;
                //statsfile.precision(std::numeric_limits<Double_t>::max_digits10);
                statsfile.precision(10);
                    /*
                statsfile << "*** " << it->Histogram()->GetName() << " ***\n"\
                    << "Human Readable Name: " << it->GetHumanReadableName() << "\n"\
                    << "Legend Text: " << it->GetLegendText() << "\n"\
                    << "Entries: " << it->Histogram()->GetEntries() << "\n"\
                    << "Number of Bins: " << it->Histogram()->GetNbinsX() << "\n"\
                    << "Underflow: " << it->Histogram()->GetBinContent(0) << "\n"\
                    << "Overflow: " << it->Histogram()->GetBinContent(it->Histogram()->GetNbinsX() + 1) << "\n"\
                    << "Min (Axis): " << it->Histogram()->GetMinimum() << "\n"\
                    << "Max (Axis): " << it->Histogram()->GetMaximum() << "\n"\
                    << "Min: " << hmin << "\n"\
                    << "Max: " << hmax << "\n"\
                    << "Min (Ignore Empty): " << hmin_ignore_empty << "\n"\
                    << "Mean: " << it->Histogram()->GetMean() << "\n"\
                    << "Standard Deviation: " << it->Histogram()->GetStdDev() << "\n"\
                    << "Standard Deviation Error: " << it->Histogram()->GetStdDevError() << "\n"\
                    << "RMS: " << it->Histogram()->GetRMS() << "\n"\
                    << "RMS Error: " << it->Histogram()->GetRMSError() << "\n"\
                    << "Integral: " << it->Histogram()->Integral() << "\n"\
                    << "\n";
                    */
                statsfile << "*** " << (*it)->Histogram()->GetName() << " ***\n"\
                    << "Human Readable Name: " << (*it)->GetHumanReadableName() << "\n"\
                    << "Legend Text: " << (*it)->GetLegendText() << "\n"\
                    << "Entries: " << (*it)->Histogram()->GetEntries() << "\n"\
                    << "Number of Bins: " << (*it)->Histogram()->GetNbinsX() << "\n"\
                    << "Underflow: " << (*it)->Histogram()->GetBinContent(0) << "\n"\
                    << "Overflow: " << (*it)->Histogram()->GetBinContent((*it)->Histogram()->GetNbinsX() + 1) << "\n"\
                    << "Min (Axis): " << (*it)->Histogram()->GetMinimum() << "\n"\
                    << "Max (Axis): " << (*it)->Histogram()->GetMaximum() << "\n"\
                    << "Min: " << hmin << "\n"\
                    << "Max: " << hmax << "\n"\
                    << "Min (Ignore Empty): " << hmin_ignore_empty << "\n"\
                    << "Mean: " << (*it)->Histogram()->GetMean() << "\n"\
                    << "Standard Deviation: " << (*it)->Histogram()->GetStdDev() << "\n"\
                    << "Standard Deviation Error: " << (*it)->Histogram()->GetStdDevError() << "\n"\
                    << "RMS: " << (*it)->Histogram()->GetRMS() << "\n"\
                    << "RMS Error: " << (*it)->Histogram()->GetRMSError() << "\n"\
                    << "Integral: " << (*it)->Histogram()->Integral() << "\n"\
                    << "\n";
                    //<< "Number of Input Entries: " << num_entries_input << "\n"\
                    //<< "Efficiency: " << (Double_t)it->Histogram()->GetEntries() / (Double_t)num_entries_input << "\n";
                    
                    // My comments on removing the above efficiency statistic:
                    // It doesn't really make sense to define efficiency in the manner above
                    // because this efficiency is associated with a "cut" rather than
                    // a histogram.
                    // It may make sense to define a histogram efficiency as the number
                    // of events that fill the histogram (not including overflow and underflow)
                    // divided by the number of events that fill the histogram (including overflow
                    // and underflow.) This would be an "efficiency" of selection by the histogram.
                    // Kind of...
                    
                statsfile.flush();
            }
        
        }
        
        // Only draw legend when required
        if(_histogram.size() > 1)
        {
            l.Draw();
        }
        
        // TODO: Remove histogram title if more than 1 item in histogram
        // or if only 1 item in graph, then do not draw legend
        
        _canvas->SaveAs((output_dir + canvas_name + std::string(".png")).c_str());
        _canvas->SaveAs((output_dir + canvas_name + std::string(".pdf")).c_str());
        _canvas->SaveAs((output_dir + canvas_name + std::string(".eps")).c_str());
        _canvas->SaveAs((output_dir + canvas_name + std::string(".C")).c_str());
        
        //statsfile.flush();
        statsfile.close();
        
    }
    
    /*
    const TCanvas *
    GetCanvasConst()
    {
        return (const TCanvas*)_canvas;
    }
    
    
    TCanvas*
    GetCanvas()
    {
        return _canvas;
    }
    */
    
    
    //void
    //Add(TH1* const histogram, const std::string& human_readable_name, const std::string& legend_text, const std::string& draw_option, const Int_t color_flag)
    //{
    //    //_histogram.push_back(std::pair<TH1*, std::string*>(histogram, new std::string(human_readable)));
    //    _histogram.push_back(TH1Data(histogram, human_readable_name, legend_text, draw_option, color_flag));
    //}

    // TODO: it is kind of annoying to have to add each histogram with unique names for both string
    // and numerical references, so it would be better to have a name generator which produced the
    // names when not specified. Then we require a function to return a reference to an internally 
    // stored vector containing all the numerical (size_t) or string format references to histograms
    // - this must be in the order of the index of the histograms in the histogram vector

    void
    Add(/*TH1* const histogram,*/ /*Double_t type ONLY!*/
        const std::string& name, const std::string& title, const Int_t n_bins, const Double_t low, const Double_t high,
        const size_t numerical_reference, const std::string& string_reference,
        const std::string& human_readable_name, const std::string& legend_text,
        const Double_t weight,
        const std::string& x_title, const std::string& y_title,
        const Bool_t sum_w2_enable,
        const std::string& draw_option,
        const Int_t color_flag = 4, const Int_t line_width = 1)
    {
        //if(_histogram_map_numeric.find(numerical_reference) == _histogram_map_numeric.end() &&
        //   _name_map_string_numeric.find(string_reference) == _name_map_string_numeric.end())
        // code does same thing, count returns 1 if entry exists, else returns 0
        if(_histogram_map_numeric.count(numerical_reference) == 0 && _name_map_string_numeric.count(string_reference) == 0)
        {
            TH1D* histogram = new TH1D(name.c_str(), title.c_str(), n_bins, low, high);
            //SetTH1DefaultXY(histogram, x_label, y_label, true); // true for Sumw2Enable - this function only called for initial initialzation
                // don't really need a function here, can do manually:
            
            histogram->SetStats(0);
    
            histogram->SetTitle("");
            
            histogram->GetXaxis()->SetTitle(x_title.c_str());
            histogram->GetYaxis()->SetTitle(y_title.c_str());
            
            histogram->GetXaxis()->SetTitleSize(GLOBAL_AXIS_TITLE_SIZE);
            histogram->GetXaxis()->SetTitleSize(GLOBAL_AXIS_TITLE_SIZE);
            
            histogram->GetYaxis()->SetLabelSize(GLOBAL_AXIS_LABEL_SIZE);
            histogram->GetYaxis()->SetLabelSize(GLOBAL_AXIS_LABEL_SIZE);
            
            if(sum_w2_enable)
            {
                histogram->Sumw2();
            }
            
            
            _histogram.push_back(new TH1Data(histogram, human_readable_name, legend_text, weight, draw_option, color_flag, line_width));
            _histogram_map_numeric.insert(std::pair<size_t, TH1Data*>(numerical_reference, _histogram.back()));
            _name_map_string_numeric.insert(std::pair<std::string, size_t>(string_reference, numerical_reference));
            histogram = nullptr;
        }
        else
        {
            throw "invalid";
        }
    }

    // well look at this you can call it something different if you want as the names are NOT saved in the file!
    // SHOULD REALLY SAVE ALL OF TH1DATA TO FILE!
    // TODO : ABOVE!
    void
    Load(TFile* const tfile,
         const std::string& name,
         const size_t numerical_reference, const std::string& string_reference,
         const std::string& human_readable_name, const std::string& legend_text,
         const Double_t weight,
         const std::string& x_title, const std::string& y_title,
         const std::string& draw_option,
         const Int_t color_flag = 4, const Int_t line_width = 1) // this function to allow user to modify axis labels etc!
    {
        //if(_histogram_map_numeric.find(numerical_reference) == _histogram_map_numeric.end() &&
        //   _name_map_string_numeric.find(string_reference) == _name_map_string_numeric.end())
        if(_histogram_map_numeric.count(numerical_reference) == 0 && _name_map_string_numeric.count(string_reference) == 0)
        {
            TH1D* histogram = (TH1D*)tfile->Get(name.c_str());
            // SetTH1DefaultXY ...
            
            // only need to do these things!
            
            histogram->GetXaxis()->SetTitle(x_title.c_str());
            histogram->GetYaxis()->SetTitle(y_title.c_str());
            
            histogram->GetXaxis()->SetTitleSize(GLOBAL_AXIS_TITLE_SIZE);
            histogram->GetXaxis()->SetTitleSize(GLOBAL_AXIS_TITLE_SIZE);
            
            histogram->GetYaxis()->SetLabelSize(GLOBAL_AXIS_LABEL_SIZE);
            histogram->GetYaxis()->SetLabelSize(GLOBAL_AXIS_LABEL_SIZE);
            
            _histogram.push_back(new TH1Data(histogram, human_readable_name, legend_text, weight, draw_option, color_flag, line_width));
            _histogram_map_numeric.insert(std::pair<size_t, TH1Data*>(numerical_reference, _histogram.back()));
            _name_map_string_numeric.insert(std::pair<std::string, size_t>(string_reference, numerical_reference));
            histogram = nullptr;
        }
        else
        {
            throw "invalid";
        }

    }
    
    void TestFill(const std::string& string_reference, const Double_t value)
    {
        std::map<std::string, size_t>::iterator it{_name_map_string_numeric.find(string_reference)};
        if(it == _name_map_string_numeric.end())
        {
            // do nothing!
        }
        else
        {
            _histogram_map_numeric.at(it->second)->GetHistogram()->Fill(value, _histogram_map_numeric.at(it->second)->GetWeight());
        }
    }
    
    void Fill(const std::string& string_reference, const Double_t value)
    {
        std::map<std::string, size_t>::iterator it{_name_map_string_numeric.find(string_reference)};
        if(it == _name_map_string_numeric.end())
        {
            throw "invalid";
        }
        else
        {
            _histogram_map_numeric.at(it->second)->GetHistogram()->Fill(value, _histogram_map_numeric.at(it->second)->GetWeight());
        }
    }


    // TODO: This should really be in the Add function but there are a lot of args in there already and basically I am lazy
    // call this function to switch canvas drawing over to log mode
    void
    SetLogMode(bool log_mode = true)
    {
        if(log_mode)
        {
            _state.SetStateMode(MultiHistogramStateMode::LOG);
            _canvas->SetLogy();
        }
        else
        {
            // TODO: what about DEFAULT ? deafult may be DEFAULT?
            _state.SetStateMode(MultiHistogramStateMode::INTEGER);
            _canvas->SetLogy(0);
        }
    }
    
    
    void SetLineWidth(const Int_t line_width)
    {
        //_state.SetLineWidth(line_width);
        _line_width = line_width;
        _line_width_enable = true;
    }
    
    
    //TODO: there are currently no exposed functions to set the line width from the default!
    // NOTE: now there are, but only by the Add functions, which requires all lines of code which call these to be edited!
    // there is no way to modify after adding, and there is no default!
    
    
    
    
    
    TH1Data&
    GetHistogramNumeric(const size_t num)
    {
        std::map<size_t, TH1Data*>::iterator it{_histogram_map_numeric.find(num)};
        if(it == _histogram_map_numeric.end())
        {
            throw "invalid";
        }
        else
        {
            return *(it->second);
        }
    }
    
    
    TH1Data&
    GetHistogramString(const std::string& str)
    {
        //std::map<std::string, TH1Data*>::iterator it{_histogram_map_string.find(str)};
        std::map<std::string, size_t>::iterator it{_name_map_string_numeric.find(str)};
        //if(it == _histogram_map_string.end())
        if(it == _name_map_string_numeric.end())
        {
            throw "invalid";
        }
        else
        {
            //return *(it->second);
            // convert iterator to get numeric name
            // return numeric name using map
            // numerical name must exist in map because it exists in the name map
            return *_histogram_map_numeric[it->second];
        }
    }
    
    // don't know why one would ever need this function - so disable
    /*
    size_t
    GetNumericName(const std::string& str)
    {
        std::map<size_t, std::string>::iterator it{_name_map_string_numeric.find(str};
        if(it == _name_map_string_numeric.end())
        {
            throw "invalid";
        }
        else
        {
            return it->second;
        }
    }
    */
    
    
    
    
};


#endif
