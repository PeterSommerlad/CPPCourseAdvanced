# Solution to Exercise 04


This is just a hint of what you might find out or consider.

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


1 `gstyle` seems to be a global pointer variable, it would be better passed as a reference parameter
2 the lines using `new` expressions would better use `std::make_unique<Type>()` instead to avoid memory leaks
  (unless there is magic in the root framework, where the type's constructors somehow register their pointers to be deleted later, which is a brittle idea)


Given the following (arbitrary chosen) constructors of the ROOT class TH1D, what violations of what we learned about relationship types can you detect and what alternative signatures would you define, in case you had a clean start:

```C++
class TH1D : public TH1, public TArrayD {

public:
   TH1D(const char *name, const char *title, Int_t nbinsx, Double_t xlow, Double_t xup);
   TH1D(const char *name, const char *title, Int_t nbinsx, const Float_t  *xbins);
   TH1D(const char *name, const char *title, Int_t nbinsx, const Double_t *xbins);
   
```


possible change:

```C++
class TH1D : public TH1, public TArrayD {

public:
   // the following constructor might actually use a type for creating the range of values 
   // separately, because it seems to me, that they form a sequens if nbinsx values between xlow and xup
   TH1D(std::string name, std::string title, Int_t nbinsx, Double_t xlow, Double_t xup);
   TH1D(std::string name, std::string title, std::span<const Float_t> xbins);
   TH1D(std::string name, std::string title, std::span<const Double_t> xbins);
   
```

An alternative to `std::span` could be a pair of iterators to denote the range, or a range abstraction, collapsing the constructor to become just a single constructor template.