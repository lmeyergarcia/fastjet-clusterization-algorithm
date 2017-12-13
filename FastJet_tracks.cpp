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
	//Arquivos de saída
	ofstream clusters_data("clusters_data.txt", ios_base::out);
	TFile *outfile = new TFile("fastJet_data.root","recreate");

	//Arquivos de entrada
	fstream all_tracks("tracks.txt", ios_base::in);
	fstream real_tracks("reais.txt", ios_base::in);

	//Histogramas all tracks 
	TH2F *all_xy = new TH2F("all_xy","All Tracks",500,-2500,2500,500,-3500,3500);
	TH1F *all_angle = new TH1F("all_angle","All Ttracks",100,0,3.15);
	TH1F *allXrealXlong_angle = new TH1F("allXrealXlong_angle","SegAngle (all tracks, real tracks, long tracks)",100,0,3.15);

	//Histogramas real tracks
	TH2F *real_xy = new TH2F("real_xy","Real Tracks",500,-2500,2500,500,-3500,3500);
	TH2F *real_etaphi = new TH2F("real_etaphi","Real Tracks",500,0,7,500,-3.15,3.15);
	TH1F *real_angle = new TH1F("real_angle","SegAngle (real tracks)",100,0,3.15);
	TH1F *real_longtracks_angle = new TH1F("real_longtracks_angle","SegAngle (real tracks)",100,0,3.15);

	//Histogramas Cluster
	TH2F *real_CA_clusters_hist_xy = new TH2F("clusters","CA FastJet Clusters (real)",500,-2500,2500,500,-3500,3500);
	TH2F *real_CA_clusters_hist_etaphi= new TH2F("clusters","CA FastJet Clusters (real)",500,0,7,500,-3.15,3.15);
	TH2F *all_CA_clusters_hist_xy = new TH2F("clusters","CA FastJet Clusters (all)",500,-2500,2500,500,-3500,3500);
	TH2F *all_CA_clusters_hist_etaphi= new TH2F("clusters","CA FastJet Clusters (all)",500,0,7,500,-3.15,3.15);

	//Variaveis do Fastjet
	double R_CA = 0.015;
	JetDefinition CA_algorithm(cambridge_algorithm, R_CA,pt_scheme);
	vector<PseudoJet> real_hits_z1000;
	vector<PseudoJet> all_hits_z1000;

	//Variaveis auxiliares
	double x1000, y1000, angle;
	int id;
	bool isLong;
	TLorentzVector hit_z1000 = TLorentzVector();

	//Todos os SimpleSegments
	while (!all_tracks.eof()){
		all_tracks >> x1000; all_tracks >> y1000; all_tracks >> angle;

		all_xy->Fill(x1000,y1000);
		all_angle->Fill(angle);

		hit_z1000.Clear();
		hit_z1000.SetPxPyPzE(x1000 ,y1000 ,10e3 ,sqrt( ( x1000* x1000) + (y1000* y1000 ) + 10e6 ) );
	
		all_hits_z1000.push_back(hit_z1000);	
	}

	//SimpleSegments Reais
	while (!real_tracks.eof()){
		real_tracks >> x1000; real_tracks >> y1000; real_tracks >> angle; 
		real_tracks >> id; real_tracks >> isLong;

		hit_z1000.Clear();
		hit_z1000.SetPxPyPzE(x1000 ,y1000 ,1e3 ,sqrt( ( x1000* x1000) + (y1000* y1000 ) + 1e6 ) );

		real_hits_z1000.push_back(hit_z1000);	

		real_angle->Fill(angle);
		real_xy->Fill(x1000,y1000);
		real_etaphi->Fill(hit_z1000.Eta() ,hit_z1000.Phi() );

		if (isLong) real_longtracks_angle->Fill(angle);

	}


	//FastJet
	//CA Algorithm - Real

	ClusterSequence cs1(real_hits_z1000, CA_algorithm);
	vector<PseudoJet> Clusters1 = sorted_by_pt(cs1.inclusive_jets(0));

	cout<<"Rodando sobre os hits reais, obteve-se " <<Clusters1.size()<<" clusters"<<endl;

	for(int i = 0; i< Clusters1.size(); i++){
		real_CA_clusters_hist_xy->Fill(Clusters1[i].px(),Clusters1[i].py()); 
		real_CA_clusters_hist_etaphi->Fill(Clusters1[i].eta(),Clusters1[i].phi_std());

		clusters_data<<"#"<<i<<" m ="<<Clusters1[i].m()<<endl;
		clusters_data<<"px	py	pt	eta	phi"<<endl;

		vector<PseudoJet> constituents = Clusters1[i].constituents();

		for(int j = 0; j < constituents.size(); j++){
			float deltaR = 0; float deltaPhi = 0;

			clusters_data << j << " " << constituents[j].px()	 << " " << constituents[j].py()  << " " << constituents[j].pt()  << " "  << constituents[j].eta() << " " << constituents[j].phi_std() << endl;

			if(j != constituents.size() - 1){
				clusters_data<<"\t\t\t\t\t\tdelta R ="<< constituents[j].delta_R(constituents[j+1])<<endl;
				deltaR = constituents[j].delta_R(constituents[j+1]);
			}
		} 
		clusters_data<<endl; 
	}


	//CA Algorithm - All 

	ClusterSequence cs2(all_hits_z1000,CA_algorithm);
	vector<PseudoJet> Clusters2 = sorted_by_pt(cs2.inclusive_jets());

	cout<<"Rodando sobre todos os hits, obteve-se "<<Clusters2.size()<<" clusters"<<endl;

	for(int i = 0; i< Clusters2.size(); i++){
		all_CA_clusters_hist_xy->Fill(Clusters2[i].px(),Clusters2[i].py()); 
		all_CA_clusters_hist_etaphi->Fill(Clusters2[i].eta(),Clusters2[i].phi_std()); 
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

	real_CA_clusters_hist_xy->Draw();
	canvas.Print("graphs/ real_CA_clusters_hist_xy.gif");
	real_CA_clusters_hist_etaphi->Draw();
	canvas.Print("graphs/ real_CA_clusters_hist_etaphi.gif");

	all_CA_clusters_hist_xy->Draw();
	canvas.Print("graphs/ all_CA_clusters_hist_xy.gif");
	all_CA_clusters_hist_etaphi->Draw();
	canvas.Print("graphs/ all_CA_clusters_hist_etaphi.gif");

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

	real_CA_clusters_hist_xy->Write("real_CA_clusters_hist_xy");
	real_CA_clusters_hist_etaphi->Write("real_CA_clusters_hist_etaphi");
	all_CA_clusters_hist_xy->Write("all_CA_clusters_hist_xy");
	all_CA_clusters_hist_etaphi->Write("all_CA_clusters_hist_etaphi");

	outfile->Close();
	

	return 0;

}
