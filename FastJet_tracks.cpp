#include<iostream>
#include<fstream>
#include "fastjet/ClusterSequence.hh"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TColor.h"
#include "TH1.h"
#include "TH2.h"
#include "TNamed.h"
#include "TArrayI.h"
using namespace std;
using namespace fastjet;

int main(){
	//Arquivo de saída
	TFile *outfile = new TFile("fastJet_data.root","recreate");

	//Arquivos de entrada
	fstream all_tracks("tracks.txt", ios_base::in);
	fstream real_tracks("reais.txt", ios_base::in);

	//Histogramas all tracks 
	TH2F *all_xy = new TH2F("all_xy","z = 1000 (all tracks)",100,-2500,2500,100,-3500,3500);
	TH1F *all_angle = new TH1F("all_angle","SegAngle (all tracks)",100,0,3.15);
	TH1F *allXrealXlong_angle = new TH1F("allXrealXlong_angle","SegAngle (all tracks, real tracks, long tracks)",100,0,3.15);

	//Histogramas real tracks
	TH2F *real_xy = new TH2F("real_xy","z = 1000 (real tracks) x X y",100,-2500,2500,100,-3500,3500);
	TH2F *real_etaphi = new TH2F("real_etaphi","z = 1000 (real tracks)eta X phi",100,0,7,100,-3.15,3.15);
	TH1F *real_angle = new TH1F("real_angle","SegAngle (real tracks)",100,0,3.15);
	TH1F *real_longtracks_angle = new TH1F("real_longtracks_angle","SegAngle (real tracks)",100,0,3.15);

	//Histogramas Cluster
	TH2F *CA_clusters_hist_xy = new TH2F("clusters","FastJet CLusters",100,-2500,2500,100,-3500,3500);
	TH2F *CA_clusters_hist_etaphi= new TH2F("clusters","FastJet CLusters",100,0,7,100,-3.15,3.15);
	TH2F *aKT_clusters_hist_xy = new TH2F("clusters","FastJet CLusters",100,-2500,2500,100,-3500,3500);
	TH2F *aKT_clusters_hist_etaphi= new TH2F("clusters","FastJet CLusters",100,0,7,100,-3.15,3.15);

	//Histogramas Trabalhosos 
	TH2F *h0 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h1 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h2 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h3 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h4 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h5 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h6 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h7 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h8 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h9 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h10 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h11 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h12 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h13 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h14 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h15 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h16 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h17 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h18 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h19 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h20 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h21 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h22 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h23 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h24 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h25 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h26 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h27 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h28 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h29 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h30 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *h31 = new TH2F("h0","h0",100,2.2,3.7,100,-1.7,1.2);
	TH2F *hlist[31] = {h1,h2,h3,h4,h5,h6,h7,h8,h9,h10,h11,h12,h13,h14,h15,h16,h17,h18,h19,h20,h21,h22,h23,h24,h25,h26,h27,h28,h29,h30,h31};

	//Variaveis do Fastjet
	double R_CA = 0.25;	
	double R_aKT= 0.25;	
	JetDefinition CA_algorithm(cambridge_algorithm, R_CA);
	JetDefinition aKT_algorithm(antikt_algorithm, R_aKT);
	vector<PseudoJet> hits_z1000_real;

	//Variaveis auxiliares
	double x1000, y1000, angle;
	int id;
	bool isLong;
	TLorentzVector hit_z1000 = TLorentzVector();
	int ids[31] = {0, 3, 8, 9, 10, 11, 12, 13, 15, 16, 17, 20, 21, 27, 36, 41, 42, 49, 51, 55, 56, 61, 67, 69, 102, 103, 107, 111, 113, 114, 115};

	//Todos os SimpleSegments
	while (!all_tracks.eof()){
		all_tracks >> x1000; all_tracks >> y1000; all_tracks >> angle;
		all_xy->Fill(x1000,y1000);
		all_angle->Fill(angle);
	}


	//SimpleSegments Reais
	while (!real_tracks.eof()){
		real_tracks >> x1000; real_tracks >> y1000; real_tracks >> angle; 
		real_tracks >> id; real_tracks >> isLong;
		
		hit_z1000.Clear();
		hit_z1000.SetPxPyPzE(x1000 ,y1000 ,1000 ,sqrt( ( x1000* x1000) + (y1000 *y1000 ) + 10e6 ) );

		hits_z1000_real.push_back(hit_z1000);	
		for (int i=0;i<31;i++) {
			if(ids[i] == id) hlist[i]->Fill(hit_z1000.Eta() ,hit_z1000.Phi() );
		}

		real_angle->Fill(angle);
		real_xy->Fill(x1000,y1000);
		real_etaphi->Fill(hit_z1000.Eta() ,hit_z1000.Phi() );
		if (isLong) real_longtracks_angle->Fill(angle);

	}
	

	//FastJet
	//CA Algorithm
	
	ClusterSequence cs1(hits_z1000_real, CA_algorithm);
	vector<PseudoJet> Clusters1 = sorted_by_pt(cs1.inclusive_jets(0));

	cout<<"O algoritimo CA formou "<<Clusters1.size()<<" clusters"<<endl;
	
	for(int i = 0; i< Clusters1.size(); i++){
	CA_clusters_hist_xy->Fill(Clusters1[i].px(),Clusters1[i].py()); 
	CA_clusters_hist_etaphi->Fill(Clusters1[i].eta(),Clusters1[i].phi_std()); 
	}
	

	//anti-KT algorithm
	
	ClusterSequence cs2(hits_z1000_real, aKT_algorithm);
	vector<PseudoJet> Clusters2 = sorted_by_pt(cs2.inclusive_jets());
	
	cout<<"O algoritimo aKT formou "<<Clusters2.size()<<" clusters"<<endl;
	
	for(int i = 0; i< Clusters2.size(); i++){
	aKT_clusters_hist_xy->Fill(Clusters2[i].px(),Clusters2[i].py()); 
	aKT_clusters_hist_etaphi->Fill(Clusters2[i].eta(),Clusters2[i].phi_std()); 
	}
	//Salvando histogramas
	TCanvas canvas;

	real_xy->Draw();	
	canvas.Print("graphs/ real_xy.gif");
	real_etaphi->Draw();	
	canvas.Print("graphs/ real_etaphi.gif");
	real_angle->Draw();	
	canvas.Print("graphs/ real_angle.gif");
	real_longtracks_angle->Draw();	
	canvas.Print("graphs/ real_longtracks_angle.gif");

	all_xy->Draw();
	canvas.Print("graphs/ all_xy.gif");
	all_angle->Draw();
	canvas.Print("graphs/ all_angle.gif");
	
	CA_clusters_hist_xy->Draw();
	canvas.Print("graphs/ CA_clusters_hist_xy.gif");
	CA_clusters_hist_etaphi->Draw();
	canvas.Print("graphs/ CA_clusters_hist_etaphi.gif");

	aKT_clusters_hist_xy->Draw();
	canvas.Print("graphs/ aKT_clusters_hist_xy.gif");
	aKT_clusters_hist_etaphi->Draw();
	canvas.Print("graphs/ aKT_clusters_hist_etaphi.gif");

	all_angle->DrawNormalized();
	real_angle->DrawNormalized("SAME");	
	real_longtracks_angle->DrawNormalized("SAME");	
	canvas.Print("graphs/NormalizedAllAngles.gif");
	canvas.Write("Angles_Comparison");

	real_xy->Write("real_xy");	
	real_etaphi->Write("real_etaphi");	
	real_angle->Write("real_angle");	
	real_longtracks_angle->Write("real_isLong_angle");

	all_xy->Write("all_xy");
	all_angle->Write("all_angle");

	CA_clusters_hist_xy->Write("CA_clusters_hist_xy");
	CA_clusters_hist_etaphi->Write("CA_clusters_hist_etaphi");
	aKT_clusters_hist_xy->Write("aKT_clusters_hist_xy");
	aKT_clusters_hist_etaphi->Write("aKT_clusters_hist_etaphi");
	hlist[0]->SetMarkerStyle(8);
	hlist[0]->Draw();
	for (int i=1;i<31;i++) {
		hlist[i]->SetMarkerStyle(8);
		hlist[i]->SetMarkerColor(28+i);
		hlist[i]->Draw("SAME ");	

	}
		canvas.Write("aaaaa");

	outfile->Close();

	return 0;

}
