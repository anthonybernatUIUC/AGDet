    #include <iostream>
    void GeHist() {

        TString title1 = "Simulated Energy Spectrum of Gammas";
        TCanvas* canvas = new TCanvas();
        canvas->SetLogy(1);
        canvas->SetTicky();
        canvas->SetTickx();
        TFile* input = new TFile("output.root", "read");
        
        TTree* tree1 = (TTree*)input->Get("GeScoring");
        double fEdepGe;
        tree1->SetBranchAddress("fEdepGe", &fEdepGe);
        int entries1 = tree1->GetEntries();

        int yHeight = 500;
        int binNo = 500;
        double xMin  = 0;
        double xMax  = 10;
        
        double fEdepMax = INT_MIN;
        double fEdepMin = INT_MAX;
        TH1F *hist1 = new TH1F("hist1", title1, binNo, xMin, xMax);
        for (int i = 0; i < entries1; i++) {
            tree1->GetEntry(i);
            hist1->Fill(fEdepGe);
            if (fEdepGe > fEdepMax) fEdepMax = fEdepGe;
            if (fEdepGe < fEdepMin) fEdepMin = fEdepGe;
        }

        std::cout << fEdepMax << std::endl;
        std::cout << fEdepMin << std::endl;

        hist1->SetLineColorAlpha(kRed, 0.35);
        hist1->GetXaxis()->SetTitle("Energy / keV");
        hist1->GetYaxis()->SetTitle("Counts");	
        hist1->SetStats(0);	
        hist1->Draw();

        // f->GetList()->Add(hist1);
        // f->Write();
    }