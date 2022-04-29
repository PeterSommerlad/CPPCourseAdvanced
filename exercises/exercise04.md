# Ding-Dang-Dong...

Since I do not recommend to use plain pointers it is hard to find useful exercises...

## root(-cause) analysis

Consider the following code from the ROOT framework tutorials (I know, this is not exactly C++)

[https://root.cern/doc/master/ratioplot2_8C.html](https://root.cern/doc/master/ratioplot2_8C.html)

```C++
void ratioplot2() {
   gStyle->SetOptStat(0);
   auto c1 = new TCanvas("c1", "fit residual simple");
   auto h1 = new TH1D("h1", "h1", 50, -5, 5);
   h1->FillRandom("gaus", 2000);
   h1->Fit("gaus", "0");
   h1->GetXaxis()->SetTitle("x");
   auto rp1 = new TRatioPlot(h1);
   rp1->Draw();
   rp1->GetLowerRefYaxis()->SetTitle("ratio");
   rp1->GetUpperRefYaxis()->SetTitle("entries");
}
```

From what we have learned on not using raw pointers, what potential problems can you identify in these few lines and how could you try to change it?

Given the following (arbitrary chosen) constructors of the ROOT class TH1D, what violations of what we learned about relationship types can you detect and what alternative signatures would you define, in case you had a clean start:

```C++
class TH1D : public TH1, public TArrayD {

public:
   TH1D(const char *name, const char *title, Int_t nbinsx, Double_t xlow, Double_t xup);
   TH1D(const char *name, const char *title, Int_t nbinsx, const Float_t  *xbins);
   TH1D(const char *name, const char *title, Int_t nbinsx, const Double_t *xbins);
   
```

Note: This is not a critique of the ROOT framework, just an exercise to open your mind to how things could be done differently with more modern C++ available.
The interfacing with Python makes many compromises or "old-style" coding practices necessary.