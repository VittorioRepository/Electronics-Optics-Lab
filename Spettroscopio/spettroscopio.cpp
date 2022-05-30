/*

SPETTROSCOPIO

*/

#include <iostream>           // ci serve per stampare a video il testo (uso di cout e endl, per esempio)
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video
#include <math.h>             // ci serve per calcolare la radice quadrata

void spettroscopio()
{
    char filename[100];

    // Scelta file
    int starter=0;
    do{
    cout << "\nQuale file vuoi analizzare?\n";
    cout << "Ordine +1:    inserisci 1\n";
    cout << "Ordine +2:    inserisci 2\n";
    cout << "Ordine -1:    inserisci 3\n";
    cout << "Ordine -2:    inserisci 4\n";
    cout << "Media degli ordini sia positivi che negativi:    inserisci 5\n";
    cout << "Media degli ordini positivi:    inserisci 6\n";
    cout << "Media degli ordini negativi:    inserisci 7\n";
    cout << "Media degli ordini sia positivi che negativi con errore degli angoli di un grado fratto 30:    inserisci 8\n";
    cout << "Media degli ordini positivi con errore degli angoli di un grado fratto 30:    inserisci 9\n";
    cout << "Media degli ordini negativi con errore degli angoli di un grado fratto 30:    inserisci 10\n";
    cin >> starter;
    if (starter!=1 && starter!=2 && starter!=3 && starter!=4 && starter!=5 && starter!=6 && starter!=7 && starter!=8 && starter!=9 && starter!=10)
        {
            cout << "VALORE INSERITO NON VALIDO" << endl;
        }
    } while (starter!=1 && starter!=2 && starter!=3 && starter!=4 && starter!=5 && starter!=6 && starter!=7 && starter!=8 && starter!=9 && starter!=10);

    if (starter==1) sprintf(filename, "+1.txt");
    if (starter==2) sprintf(filename, "+2.txt");
    if (starter==3) sprintf(filename, "-1.txt");
    if (starter==4) sprintf(filename, "-2.txt");
    if (starter==5) sprintf(filename, "mediaordini.txt");
    if (starter==6) sprintf(filename, "mediapositivi.txt");
    if (starter==7) sprintf(filename, "medianegativi.txt");
    if (starter==8) sprintf(filename, "mediaordini_1.txt");
    if (starter==9) sprintf(filename, "mediapositivi_1.txt");
    if (starter==10) sprintf(filename, "medianegativi_1.txt");

    // LETTURA DATI

    FILE *input = fopen(filename, "r" );

    if(!input)
    {
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }

    // Conteggio

    float temp_val;
    int   npoints = 0;

    while(!feof(input))
    {
        fscanf(input,"%f\n",&temp_val);
        ++npoints;
    }

    npoints = npoints/4;
    cout << "\nSono state raccolte: " << npoints << " misure di coppie lunghezza d'onda - indice di rifrazione" << endl;

    // Lettura

    rewind(input);
    float *lambda = new float[npoints];
    float *err_lambda = new float[npoints];
    float *n = new float[npoints];
    float *err_n = new float[npoints];

    int i=0;
    while(!feof(input))
    {
        if(i<npoints){
            fscanf(input,"%f\n",&temp_val);
            lambda[i] = temp_val;
        }
        else if(i<2*npoints){
            fscanf(input,"%f\n",&temp_val);
            err_lambda[i-npoints] = temp_val;
        }
        else if(i<3*npoints){
            fscanf(input,"%f\n",&temp_val);
            n[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints){
            fscanf(input,"%f\n",&temp_val);
            err_n[i-3*npoints] = temp_val;
        }
        else if(i<5*npoints){
            fscanf(input,"%f\n",&temp_val);
            err_n[i-4*npoints] = temp_val;
        }
        ++i;

    }

    fclose(input);

    // Stampa dei valori

    int stampa = 6;

    do
    {
        cout << "Vuoi stampare i valori raccolti a schermo?\nSI:   INSERISCI 0\nNO:   INSERISCI 1\n";
        cin >> stampa;
        if (stampa!=0 && stampa!=1) cout << "Hai inserito un valore non consentito.\n";
    } while (stampa!=0 && stampa!=1);

    if (stampa==0)
    {
        cout << "VALORI" << endl;
        for(int j=0;j<npoints;j++){
            cout << j+1 << ":" << n[j] << " +- " << err_n[j] << ", " << lambda[j] << " +- " << err_lambda[j] << endl;
        }

    }




    // PLOT E FIT

    TCanvas *n_lambda = new TCanvas("Spettroscopio","Spettroscopio",200,10,1000,700);
    n_lambda->SetFillColor(0);
    n_lambda->cd();
    TGraphErrors *g_n_lambda = new TGraphErrors(npoints,lambda,n,err_lambda,err_n);

    // Abbellimenti
    g_n_lambda->SetMarkerSize(0.6);
    g_n_lambda->SetMarkerStyle(21);
    g_n_lambda->SetTitle("n(#lambda) = a +  ( b / #lambda^2 )"); // Titolo del grafico
    g_n_lambda->GetYaxis()->SetTitle("Indice di rifrazione n"); // Titoli degli assi
    g_n_lambda->GetXaxis()->SetTitle("Lunghezza d'onda #lambda [nm]");

    //Per impostare scala logaritmica:
    //su asse x:
    //n_lambda->SetLogx(1);
    //su asse y:
    //n_lambda->SetLogy(1);

    g_n_lambda->Draw("AP");


    // n(lambda)

    TF1 *function = new TF1("Fit","[0]+([1]/pow(x,2))",100,1000);

    //function->SetParameter(0,4);
    //function->SetParameter(1,0);
    //function->SetParameter(2,0);
    function->SetLineColor(4); // Blu
    g_n_lambda->Fit(function,"RM+");




    // Polinomiale

    TCanvas *n_lambda_2 = new TCanvas("Spettroscopio_2","Spettroscopio_2",200,10,1000,700);
    n_lambda_2->SetFillColor(0);
    n_lambda_2->cd();
    TGraphErrors *g_n_lambda_2 = new TGraphErrors(npoints,lambda,n,err_lambda,err_n);

    // Abbellimenti
    g_n_lambda_2->SetMarkerSize(0.6);
    g_n_lambda_2->SetMarkerStyle(21);
    g_n_lambda_2->SetTitle("n(#lambda) = a + b #lambda + c #lambda^2"); // Titolo del grafico
    g_n_lambda_2->GetYaxis()->SetTitle("Indice di rifrazione n"); // Titoli degli assi
    g_n_lambda_2->GetXaxis()->SetTitle("Lunghezza d'onda #lambda [nm]");
    g_n_lambda_2->Draw("AP");

    TF1 *function2 = new TF1("Fit","[0]+[1]*x+[2]*pow(x,2)",100,1000);


    function2->SetParameter(0,1);
    function2->SetParameter(1,-0.5e-3);
    function2->SetParameter(2,1e-7);

    if (starter==10){
        function2->SetParameter(0,1);
        function2->SetParameter(1,-0.5e-3);
        function2->SetParameter(2,1e-6);
    }

    function2->SetLineColor(3); // verde

    g_n_lambda_2->Fit(function2,"RM+");




    // Grafico a dispersione n(#lambda)

    TCanvas *n_lambda_3 = new TCanvas("Spettroscopio_3","Spettroscopio_3",200,10,1000,700);
    n_lambda_3->SetFillColor(0);
    n_lambda_3->cd();
    TGraphErrors *g_n_lambda_3 = new TGraphErrors(npoints,lambda,n,err_lambda,err_n);

    // Abbellimenti

    g_n_lambda_3->SetMarkerSize(0.6);
    g_n_lambda_3->SetMarkerStyle(21);
    g_n_lambda_3->SetTitle("Grafico a dispersione n(#lambda)"); // Titolo del grafico
    g_n_lambda_3->GetYaxis()->SetTitle("Indice di rifrazione n"); // Titoli degli assi
    g_n_lambda_3->GetXaxis()->SetTitle("Lunghezza d'onda #lambda [nm]");
    g_n_lambda_3->Draw("AP");

    //Per impostare scala logaritmica:
    //su asse x:
    // g_n_lambda_3->SetLogx(1);
    //su asse y:
    //filter->SetLogy(1);
    g_n_lambda_3->Draw("AP");

    gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph



}
