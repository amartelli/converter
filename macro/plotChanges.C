

void plotChanges(){


  float etaBins[4] = {0., 0.9, 1.4, 2.5};
  float ptBins[36] = {0., 0.1823, 0.2227, 0.2720, 0.3323, 0.4060, 0.4959, 0.6058, 0.7401, 0.9041, 1.1044, 
		      1.3492, 1.6481, 2.0134, 2.4595, 3.0045, 3.6703, 4.4837, 5.4772, 6.6910, 8.1737, 
		      9.9849, 12.1976, 14.9005, 18.2024, 22.2360, 27.1635, 33.1828, 40.5360, 49.5187, 60.4919, 
		      73.8967, 90.2720, 110.2760, 134.7130, 200.};


  
  
  float valD0_pT_reso_eta[4][36] = {   {0., 0.3543, 0.2809, 0.2304, 0.1917, 0.1737, 0.1434, 0.1060, 0.0893, 0.0753, 0.0670, 
					0.0577, 0.0524, 0.0452, 0.0376, 0.0350, 0.0324, 0.0283, 0.0258, 0.0237, 0.0211, 
					0.0191, 0.0164, 0.0150, 0.0143, 0.0130, 0.0130, 0.0116, 0.0116, 0.0110, 0.0110,
					0.0110, 0.0104, 0.0109, 0.0110, 0.0110}, 
				       {0., 0.4564, 0.3580, 0.3010, 0.2353, 0.2026, 0.1595, 0.1383, 0.1119, 0.0926, 0.0816, 
					0.0663, 0.0553, 0.0488, 0.0431, 0.0399, 0.0357, 0.0313, 0.0277, 0.0233, 0.0221, 
					0.0214, 0.0180, 0.0155, 0.0141, 0.0128, 0.0134, 0.0121, 0.0108, 0.0101, 0.0101, 0.0101, 0.0102,
					0.0088, 0.0095, 0.0095}, 
				       {0., 0.6970, 0.6046, 0.5315, 0.4306, 0.3398, 0.2788, 0.2387, 0.1814, 0.1557, 0.1230, 
					0.1009, 0.0914, 0.0767, 0.0638, 0.0544, 0.0468, 0.0425, 0.0385, 0.0331, 0.0278, 
					0.0256, 0.0236, 0.0217, 0.0196, 0.0176, 0.0165, 0.0157, 0.0150, 0.0144, 0.0144, 0.0137, 0.0130,  
					0.0137, 0.0137, 0.0137}, 
				       {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.}   };
  

  
  float valDZ_pT_reso_eta[4][36] = {   {0., 0.3693, 0.3135, 0.3125, 0.2578, 0.2221, 0.1936, 0.1686, 0.1351, 0.1113, 0.0983, 0.0882, 0.0786, 0.0684, 
					0.0615, 0.0551, 0.0516, 0.0484, 0.0450, 0.0416, 0.0416, 0.0382, 0.0350, 0.0317, 0.0316, 0.0316, 0.0316, 0.0348, 0.0316, 0.0316, 
					0.0316, 0.0284, 0.0283, 0.0315, 0.0318, 0.0318}, 
				       {0., 0.7062, 0.6010, 0.5992, 0.4959, 0.3877, 0.3199, 0.2649, 0.2518, 0.1982, 0.1587, 0.1399, 0.1199, 0.1031, 0.0967, 
					0.0805, 0.0736, 0.0707, 0.0603, 0.0609, 0.0541, 0.0511, 0.0443, 0.0409, 0.0408, 0.0409, 0.0377, 0.0375, 0.0377, 0.0342, 0.0342, 0.0343, 
					0.0343, 0.0309, 0.0310, 0.0310},
				       {0., 2.1717, 2.0715, 2.0679, 1.7679, 1.4393, 1.1997, 0.9800, 0.8251, 0.6695, 0.5545, 0.4366, 0.3711, 0.3319, 0.2721, 0.2443, 0.2085, 
					0.1816, 0.1641, 0.1451, 0.1317, 0.1117, 0.1020, 0.1017, 0.0983, 0.0882, 0.0847, 0.0814, 0.0784, 0.0817, 0.0750, 0.0816, 0.0820, 
					0.0814,0.0850, 0.0850},
				       {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.}   };



  float chHadTk_ptEff[4] = {0., 0.5, 1., 10.};
  float chHadTk_etaEff[4] = {0., 1.2, 2.5, 4.};
  float chHadTk_Eff[4][4] = { {0., 0.9*0.75, 0.95, 0.95}, { 0., 0.85*0.75, 0.9, 0.9}, {0., 0.8*0.75, 0.85, 0.85}, {0., 0., 0., 0.}};

  float muoTk_ptEff[4] = {0., 0.5, 1., 10.};
  float muoTk_etaEff[4] = {0., 1.2, 2.8, 4.};
  float muoTk_Eff[4][4] = { { 0., 1., 1., 1.}, { 0., 1., 1., 1.}, {0., 0.95, 0.95, 0.95}, {0., 0., 0., 0.} };


  float eleTk_ptEff[4] = {0., 0.5, 1., 10.};
  float eleTk_etaEff[4] = {0., 1.2, 2.5, 4.};
  //  float eleTk_Eff[4][3] = { {0., 0., 0.}, { 0., 0.9, 0.95}, { 0., 0.85, (0.90)/(-0.033*log10(pt) + 1.033)}, {0., 0.8, (0.85)/(-0.033*log10(pt) + 1.033)} };
  float eleTk_Eff[4][4] = { { 0., 0.9, 0.95}, { 0., 0.85,  0.87, 0.87}, {0., 0.8, 0.87, 0.87}, {0., 0., 0., 0.} };


  float gamma_ptEff[4] = {0., 1., 5., 10.};
  float gamma_etaEff[3] = {0., 2.5, 4.};
  float gamma_Eff[3][4] = { {0., 0., 0., 0.}, { 0., 0.7, 0.85, 0.95}, {0., 0.6, 0.8, 0.9} };


  float ele_ptEff[9] = {0., 2., 4., 6., 8., 10., 30., 50., 70.};
  float ele_etaEff[6] = {0., 1.45, 1.55, 2., 2.5, 4.};
  float ele_Eff[6][9] = { {0., 0., 0., 0., 0., 0., 0., 0., 0.}, 
			  {0., 0.05, 0.5, 0.7, 0.85, 0.94, 0.97, 0.98, 1.},
			  {0., 0.05, 0.35, 0.35, 0.35, 0.4, 0.45, 0.45, 0.55},
			  {0., 0.05, 0.75, 0.75, 0.75, 0.85, 0.95, 0.95, 1.},
			  {0., 0.05, 0.65, 0.65, 0.65, 0.75, 0.90, 0.90, 0.90},
			  {0., 0.05, 0.05, 0.65, 0.65, 0.75, 0.9, 0.9, 0.9} };



  float muo_ptEff[11] = {0., 2., 4., 6., 8., 10., 20., 35., 50., 70., 1400.};
  float muo_etaEff[7] = {0., 0.5, 1., 1.5, 2., 2.5, 4.};
  float muo_Eff[7][11] = { {0., 0.04, 0.43, 0.53, 0.68, 0.81, 0.91, 0.96, 0.91, 0.91}, 
			   {0., 0.05, 0.47, 0.56, 0.69, 0.79, 0.93, 0.94, 0.91, 0.91}, 
			   {0., 0.16, 0.48, 0.53, 0.66, 0.79, 0.89, 0.95, 0.91, 0.91}, 
			   {0., 0.24, 0.44, 0.51, 0.71, 0.77, 0.91, 0.92, 0.91, 0.91}, 
			   {0., 0.23, 0.35, 0.43, 0.57, 0.63, 0.71, 0.76, 0.81, 0.81}, 
			   {0., 0.05, 0.65, 0.65, 0.65, 0.65, 0.75, 0.90, 0.90, 0.90}, 
			   {0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0.}};





  float chHadTk_ptReso[5] = {0., 1., 10., 100., 200.};
  float chHadTk_etaReso[21] = {0., 0.2, 0.4, 0.6, 0.8, 1., 1.2, 1.4, 1.6, 1.8, 2., 2.2, 2.4, 2.6, 2.8, 3., 3.2, 3.4, 3.6, 3.8, 4.};
  float chHadTk_Reso[21][5] = { {0.00457888, 0.004759, 0.006863, 0.013866, 0.013866},
			      {0.00505011, 0.005182, 0.007063, 0.013758, 0.013758}, 
			      {0.00510573, 0.005198, 0.006997, 0.0136155, 0.0136155}, 
			      {0.00578020, 0.00578, 0.007299, 0.0137655, 0.0137655}, 
			      {0.00728723, 0.007163, 0.008531, 0.0156435, 0.0156435},
			      {0.01045117, 0.010247, 0.011709, 0.0208005, 0.0208005}, 
			      {0.01477199, 0.01426, 0.015016, 0.0252, 0.0252}, 
			      {0.01731474, 0.016483, 0.016639, 0.0272415, 0.0272415},
			      {0.01942025, 0.017752, 0.016709, 0.0270585, 0.0270585},
			      {0.02201432, 0.019346, 0.017812, 0.030147, 0.030147},
			      {0.02574300, 0.021271, 0.017721, 0.0304335, 0.0304335},
			      {0.02885821, 0.023478, 0.018873, 0.032286, 0.032286},
			      {0.03204812, 0.0272, 0.022618, 0.0367155, 0.0367155},
			      {0.03950405, 0.03396, 0.028506, 0.045588, 0.045588},
			      {0.04084751, 0.033728, 0.025984, 0.028884, 0.028884},
			      {0.04532425, 0.035336, 0.023811, 0.0375795, 0.0375795},
			      {0.06418925, 0.047969, 0.029051, 0.046065, 0.046065},
			      {0.07682500, 0.058785, 0.038194, 0.0609435, 0.0609435},
			      {0.09796358, 0.074932, 0.048905, 0.0785175, 0.0785175},
			      {0.13415929, 0.101027, 0.064052, 0.1044255, 0.1044255}, 
			      {0., 0., 0., 0., 0.}};



  //
  int iColors[4] = {kRed, kBlue, kGreen+2, kBlack};
  //  int iColors[4] = {kBlue, kBlue+2, kCyan, kAzure+7};

  int etaN = 3;
  int ptN = 35;

  TProfile* d0_vsPt[4];
  TProfile* d0_vsEta[4];

  TProfile* dZ_vsPt[4];
  TProfile* dZ_vsEta[4];

  for(int ij=0; ij<4; ++ij){
    d0_vsEta[ij] = new TProfile(Form("d0_vsEta%d", ij), "", etaN, etaBins);
    d0_vsPt[ij] = new TProfile(Form("d0_vsPt%d", ij), "", ptN, ptBins);
    dZ_vsEta[ij] = new TProfile(Form("dZ_vsEta%d", ij), "", etaN, etaBins);
    dZ_vsPt[ij] = new TProfile(Form("dZ_vsPt%d", ij), "", ptN, ptBins);
  }


  float d0options[4] = {1., 1.2, 5., 10.};
  float dZoptions[4] = {1., 1.05, 1.3, 1.05};

  for(int ij=0; ij< etaN; ++ij){
    for(int kl=0; kl< ptN; ++kl){

      float d0val = valD0_pT_reso_eta[ij][kl];
      float dZval = valDZ_pT_reso_eta[ij][kl];
      for(int yu=0; yu<4; ++yu){
	d0_vsPt[yu]->Fill(ptBins[kl], d0val * d0options[yu]);
	d0_vsEta[yu]->Fill(etaBins[ij], d0val * d0options[yu]);
	// d0_vsEta[yu]->SetBinContent(d0_vsEta[yu]->FindBin(etaBins[ij]), d0val * d0options[yu]);
	// d0_vsPt[yu]->SetBinContent(d0_vsPt[yu]->FindBin(ptBins[kl]), d0val * d0options[yu]);

	d0_vsPt[yu]->SetLineColor(iColors[yu]);
	d0_vsEta[yu]->SetLineColor(iColors[yu]);
	d0_vsPt[yu]->SetLineWidth(2);
	d0_vsEta[yu]->SetLineWidth(2);
	d0_vsPt[yu]->SetMarkerColor(iColors[yu]);
	d0_vsEta[yu]->SetMarkerColor(iColors[yu]);

	//	std::cout << " d0_vsEta[yu]->FindBin(etaBins[ij]) = " << d0_vsEta[yu]->FindBin(etaBins[ij]) << std::endl;

	// dZ_vsEta[yu]->SetBinContent(dZ_vsEta[yu]->FindBin(etaBins[ij]), dZval * dZoptions[yu]);
	// dZ_vsPt[yu]->SetBinContent(dZ_vsPt[yu]->FindBin(ptBins[kl]), dZval * dZoptions[yu]);

	dZ_vsPt[yu]->Fill(ptBins[kl], dZval * dZoptions[yu]);
	dZ_vsEta[yu]->Fill(etaBins[ij], dZval * dZoptions[yu]);
	dZ_vsPt[yu]->SetLineColor(iColors[yu]);
	dZ_vsEta[yu]->SetLineColor(iColors[yu]);
	dZ_vsPt[yu]->SetLineWidth(2);
	dZ_vsEta[yu]->SetLineWidth(2);
	dZ_vsPt[yu]->SetMarkerColor(iColors[yu]);
	dZ_vsEta[yu]->SetMarkerColor(iColors[yu]);

      }

    }
  }


  int etaEff = 3;
  int ptEff = 3;

  TProfile* chHadTkEff_vsPt[4];
  TProfile* chHadTkEff_vsEta[4];

  TProfile* muoTkEff_vsPt = new TProfile("muoTkEff_vsPt", "", ptEff, muoTk_ptEff);
  TProfile* muoTkEff_vsEta = new TProfile("muoTkEff_vsEta", "", etaEff, muoTk_etaEff);

  TProfile* eleTkEff_vsPt = new TProfile("eleTkEff_vsPt", "", ptEff, eleTk_ptEff);
  TProfile* eleTkEff_vsEta = new TProfile("eleTkEff_vsEta", "", etaEff, eleTk_etaEff);

  for(int ij=0; ij<4; ++ij){
    chHadTkEff_vsPt[ij] = new TProfile(Form("chHadTkEff_vsPt%d", ij), "", ptEff, chHadTk_ptEff);
    chHadTkEff_vsEta[ij] = new TProfile(Form("chHadTkEff_vsEta%d", ij), "", etaEff, chHadTk_etaEff);
  }
  

  float chHadEoptions[4] = {1., 0.98, 0.5, 1.};

  for(int ij=0; ij< etaEff; ++ij){
    for(int kl=0; kl< ptEff; ++kl){
      
      float chHadEffval = chHadTk_Eff[ij][kl];
      for(int yu=0; yu<4; ++yu){
	chHadTkEff_vsPt[yu]->Fill(chHadTk_ptEff[kl], chHadEffval * chHadEoptions[yu]);
	 chHadTkEff_vsEta[yu]->Fill(chHadTk_etaEff[ij], chHadEffval * chHadEoptions[yu]);
	chHadTkEff_vsPt[yu]->SetLineColor(iColors[yu]);
	chHadTkEff_vsEta[yu]->SetLineColor(iColors[yu]);
	chHadTkEff_vsPt[yu]->SetLineWidth(2);
	chHadTkEff_vsEta[yu]->SetLineWidth(2);
	chHadTkEff_vsPt[yu]->SetMarkerColor(iColors[yu]);
	chHadTkEff_vsEta[yu]->SetMarkerColor(iColors[yu]);

	// chHadTkEff_vsEta[yu]->SetBinContent(chHadTkEff_vsEta[yu]->FindBin(chHadTk_etaEff[ij]), chHadEffval * chHadEoptions[yu]);
	// chHadTkEff_vsPt[yu]->SetBinContent(chHadTkEff_vsPt[yu]->FindBin(chHadTk_ptEff[kl]), chHadEffval * chHadEoptions[yu]);
	
      }

      muoTkEff_vsPt->Fill(muoTk_ptEff[kl], muoTk_Eff[ij][kl]);
      muoTkEff_vsEta->Fill(muoTk_etaEff[ij], muoTk_Eff[ij][kl]);

      eleTkEff_vsPt->Fill(eleTk_ptEff[kl], eleTk_Eff[ij][kl]);
      eleTkEff_vsEta->Fill(eleTk_etaEff[ij], eleTk_Eff[ij][kl]);

    }
  }


  int etaReso = 20;
  int ptReso = 4;

  TProfile* chHadTkReso_vsPt[4];
  TProfile* chHadTkReso_vsEta[4];

  for(int ij=0; ij<4; ++ij){
    chHadTkReso_vsPt[ij] = new TProfile(Form("chHadTkReso_vsPt%d", ij), "", ptReso, chHadTk_ptReso);
    chHadTkReso_vsEta[ij] = new TProfile(Form("chHadTkReso_vsEta%d",ij), "", etaReso, chHadTk_etaReso);
  }

  float chHadRoptions[4] = {1., 2., 10., 1.};

  for(int ij=0; ij< etaReso; ++ij){
    for(int kl=0; kl< ptReso; ++kl){

      float chHadReso = chHadTk_Reso[ij][kl];
      for(int yu=0; yu<4; ++yu){
	if(chHadTk_ptReso[kl] != 0){
	  chHadTkReso_vsPt[yu]->Fill(chHadTk_ptReso[kl], chHadReso * chHadRoptions[yu] / chHadTk_ptReso[kl]);
	  chHadTkReso_vsEta[yu]->Fill(chHadTk_etaReso[ij], chHadReso * chHadRoptions[yu] / chHadTk_ptReso[kl]);

	// chHadTkReso_vsEta[yu]->SetBinContent(chHadTkReso_vsEta[yu]->FindBin(chHadTk_etaReso[ij]), chHadReso * chHadRoptions[yu] / chHadTk_ptReso[kl]);
	// chHadTkReso_vsPt[yu]->SetBinContent(chHadTkReso_vsPt[yu]->FindBin(chHadTk_ptReso[kl]), chHadReso * chHadRoptions[yu] / chHadTk_ptReso[kl]);

	}
	else{
	  // chHadTkReso_vsPt[yu]->SetBinContent(chHadTkReso_vsPt[yu]->FindBin(chHadTk_ptReso[kl]), 0.);
	  // chHadTkReso_vsEta[yu]->SetBinContent(chHadTkReso_vsEta[yu]->FindBin(chHadTk_etaReso[ij]), 0.);

	  chHadTkReso_vsPt[yu]->Fill(chHadTk_ptReso[kl], 0.);
	  chHadTkReso_vsEta[yu]->Fill(chHadTk_etaReso[ij], 0.);
	}
	chHadTkReso_vsPt[yu]->SetLineColor(iColors[yu]);
	chHadTkReso_vsEta[yu]->SetLineColor(iColors[yu]);
	chHadTkReso_vsPt[yu]->SetLineWidth(2);
	chHadTkReso_vsEta[yu]->SetLineWidth(2);
	chHadTkReso_vsPt[yu]->SetMarkerColor(iColors[yu]);
	chHadTkReso_vsEta[yu]->SetMarkerColor(iColors[yu]);

      }

    }
  }




  gStyle->SetOptStat(0);

  TLegend *legTGM = new TLegend(0.80,0.70,0.90,0.90,NULL,"brNDC");
  legTGM->SetTextFont(42);
  legTGM->SetTextSize(0.04);
  legTGM->SetFillStyle(0);
  legTGM->SetFillColor(kWhite);
  legTGM->SetLineColor(kWhite);
  legTGM->SetShadowColor(kWhite);
  for(int io=0; io<4; ++io)
    legTGM->AddEntry(d0_vsPt[io], Form("v%d ", io), "l");




  TCanvas* cd0pt = new TCanvas();
  gPad->SetLogy();
  gPad->SetLogx();
  cd0pt->cd();
  d0_vsPt[0]->GetYaxis()->SetRangeUser(0.01, 10.);
  d0_vsPt[0]->GetXaxis()->SetRangeUser(0.01, 150.);
  d0_vsPt[0]->GetXaxis()->SetTitle("p_{T}");
  d0_vsPt[0]->GetYaxis()->SetTitle("#sigma_{d0} mm");
  d0_vsPt[0]->Draw("h");
  for(int ij=1; ij<4; ++ij)d0_vsPt[ij]->Draw("h, same");  
  legTGM->Draw("same");
  cd0pt->Print("plotCompare/d0_vsPt.png", "png");

  TCanvas* cd0et = new TCanvas();
  cd0et->cd();
  gPad->SetLogy();
  d0_vsEta[0]->GetYaxis()->SetRangeUser(0.01, 2.);
  d0_vsEta[0]->GetXaxis()->SetTitle("|#eta|");
  d0_vsEta[0]->GetYaxis()->SetTitle("#sigma_{d0} mm");
  d0_vsEta[0]->Draw("h");
  for(int ij=1; ij<4; ++ij)d0_vsEta[ij]->Draw("h, same");
  legTGM->Draw("same");
  cd0et->Print("plotCompare/d0_vsEta.png", "png");

  TCanvas* cdZpt = new TCanvas();
  gPad->SetLogy();
  gPad->SetLogx();
  cdZpt->cd();
  dZ_vsPt[0]->GetYaxis()->SetRangeUser(0.01, 2.);
  dZ_vsPt[0]->GetXaxis()->SetRangeUser(0.001, 150.);
  dZ_vsPt[0]->GetXaxis()->SetTitle("p_{T}");
  dZ_vsPt[0]->GetYaxis()->SetTitle("#sigma_{dZ} mm");
  dZ_vsPt[0]->Draw("h");
  for(int ij=1; ij<4; ++ij)dZ_vsPt[ij]->Draw("h, same");  
  legTGM->Draw("same");
  cdZpt->Print("plotCompare/dZ_vsPt.png", "png");

  TCanvas* cdZet = new TCanvas();
  cdZet->cd();
  gPad->SetLogy();
  dZ_vsEta[0]->GetYaxis()->SetRangeUser(0.01, 2.);
  dZ_vsEta[0]->GetXaxis()->SetTitle("|#eta|");
  dZ_vsEta[0]->GetYaxis()->SetTitle("#sigma_{dZ} mm");
  dZ_vsEta[0]->Draw("h");
  for(int ij=1; ij<4; ++ij)dZ_vsEta[ij]->Draw("h, same");
  legTGM->Draw("same");
  cdZet->Print("plotCompare/dZ_vsEta.png", "png");


  TCanvas* cHadEffpt = new TCanvas();
  // gPad->SetLogy();
  // gPad->SetLogx();
  cHadEffpt->cd();
  chHadTkEff_vsPt[0]->GetYaxis()->SetRangeUser(0.01, 1.5);
  chHadTkEff_vsPt[0]->GetXaxis()->SetRangeUser(0.01, 5.);
  chHadTkEff_vsPt[0]->GetXaxis()->SetTitle("p_{T} (charged hadron)");
  chHadTkEff_vsPt[0]->GetYaxis()->SetTitle("trk eff");
  chHadTkEff_vsPt[0]->Draw("h");
  for(int ij=1; ij<4; ++ij)chHadTkEff_vsPt[ij]->Draw("h, same");  
  legTGM->Draw("same");
  cHadEffpt->Print("plotCompare/chargedHadronEfficiency_vsPt.png", "png");

  TCanvas* cHadEffet = new TCanvas();
  cHadEffet->cd();
  chHadTkEff_vsEta[0]->GetYaxis()->SetRangeUser(0.01, 1.5);
  //  chHadTkEff_vsEta[0]->GetXaxis()->SetRangeUser(0.01, 5.);
  chHadTkEff_vsEta[0]->GetXaxis()->SetTitle("|#eta| (charged hadron)");
  chHadTkEff_vsEta[0]->GetYaxis()->SetTitle("trk eff");
  chHadTkEff_vsEta[0]->Draw("h");
  for(int ij=1; ij<4; ++ij)chHadTkEff_vsEta[ij]->Draw("h, same");  
  legTGM->Draw("same");
  cHadEffet->Print("plotCompare/chargedHadronEfficiency_vsEta.png", "png");

  TCanvas* cHadResopt = new TCanvas();
  gPad->SetLogy();
  //  gPad->SetLogx();
  cHadResopt->cd();
  chHadTkReso_vsPt[0]->GetYaxis()->SetRangeUser(0.001, 1.1);
  //  chHadTkReso_vsPt[0]->GetXaxis()->SetRangeUser(0.001, 150.);
  chHadTkReso_vsPt[0]->GetXaxis()->SetTitle("p_{T} (charged hadron)");
  chHadTkReso_vsPt[0]->GetYaxis()->SetTitle("#sigma_{p} / p ");
  chHadTkReso_vsPt[0]->Draw("h");
  for(int ij=1; ij<4; ++ij)chHadTkReso_vsPt[ij]->Draw("h, same");  
  legTGM->Draw("same");
  cHadResopt->Print("plotCompare/chargedHadronResolution_vsPt.png", "png");


  TCanvas* cHadResoet = new TCanvas();
  gPad->SetLogy();
  //  gPad->SetLogx();
  cHadResoet->cd();
  chHadTkReso_vsEta[0]->GetYaxis()->SetRangeUser(0.001, 1.1);
  //  chHadTkReso_vsEta[0]->GetXaxis()->SetRangeUser(0.001, 150.);
  chHadTkReso_vsEta[0]->GetXaxis()->SetTitle("|#eta| (charged hadron)");
  chHadTkReso_vsEta[0]->GetYaxis()->SetTitle("#sigma_{p} / p ");
  chHadTkReso_vsEta[0]->Draw("h");
  for(int ij=1; ij<4; ++ij)chHadTkReso_vsEta[ij]->Draw("h, same");  
  legTGM->Draw("same");
  cHadResoet->Print("plotCompare/chargedHadronResolution_vsEta.png", "png");




}

