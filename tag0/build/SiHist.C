void SiHist() {

    TString title1 = "Simulated Energy Spectrum of Alphas";
    TCanvas* canvas = new TCanvas();
    canvas->SetLogy(1);
    canvas->SetTicky();
    canvas->SetTickx();
    // TPad* pad1 = new TPad();
    // pad1->Draw();
    // pad1->cd();
    // pad1->SetLogy(1);
    // pad1->SetTicky();
    // pad1->SetTickx();
    // pad1->SetGridy();

    // TFile* f = new TFile("testingtestingtesting.root", "recreate");
    TFile* input = new TFile("output.root", "read");
    
    TTree* tree1 = (TTree*)input->Get("SiScoring");
    double fEdepSi;
	tree1->SetBranchAddress("fEdepSi", &fEdepSi);
    int entries1 = tree1->GetEntries();

    int yHeight = 500;
    int binNo = 500;
    double xMin  = 0;
    double xMax  = 2.5;
    
    TH1F *hist1 = new TH1F("hist1", title1, binNo, xMin, xMax);
    for (int i = 0; i < entries1; i++) {
        tree1->GetEntry(i);
        hist1->Fill(fEdepSi);
    }

    hist1->SetLineColorAlpha(kRed, 0.35);
    hist1->GetXaxis()->SetTitle("Energy / MeV");
    hist1->GetYaxis()->SetTitle("Counts");	
	hist1->SetStats(0);	
	hist1->Draw();

    TLine *l1 = new TLine(1.77, 0, 1.77, 100);
    l1->SetLineWidth(1);
    l1->SetLineStyle(kDashed);
    l1->Draw();
    TLine *l2 = new TLine(1.47, 0, 1.47, 400);
    l2->SetLineWidth(1);
    l2->SetLineStyle(kDashed);
    l2->Draw();

    // f->GetList()->Add(hist1);
    // f->Write();
}