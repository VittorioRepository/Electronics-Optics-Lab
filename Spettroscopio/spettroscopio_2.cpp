/*

SPETTROSCOPIO 2 -- SPETTROFOTOMETRO

*/

#include <iostream>           // ci serve per stampare a video il testo (uso di cout e endl, per esempio)
#include <TGraphErrors.h>     // ci serve per istanziare grafici
#include <TAxis.h>            // ci serve per manipolare gli assi dei grafici
#include <TCanvas.h>          // ci serve per disegnare i grafici
#include <TF1.h>              // ci serve per scrivere le funzioni con cui fittare i grafici
#include <iomanip>            // ci serve per manipolare l'output a video
#include <math.h>             // ci serve per calcolare la radice quadrata

void spettroscopio_2()
{
    char filename[100];

    // Scelta file
    int starter=0;
    do{
    cout << "\nQuale file vuoi analizzare?\n";
    cout << "Spettrofotometro 1:    inserisci 1\n";
    cout << "Spettrofotometro 2:    inserisci 2\n";
    cout << "Spettrofotometro 3:    inserisci 3\n";
    cin >> starter;
    if (starter!=1 && starter!=2 && starter!=3)
        {
            cout << "VALORE INSERITO NON VALIDO" << endl;
        }
    } while (starter!=1 && starter!=2 && starter!=3);

    if (starter==1) sprintf(filename, "spettrofotometro_1.txt");
    if (starter==2) sprintf(filename, "spettrofotometro_2.txt");
    if (starter==3) sprintf(filename, "spettrofotometro_3.txt");

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

    cout << "\nSono state raccolte: " << npoints << " misure di coppie lunghezza d'onda - intensità" << endl;

    // Lettura

    rewind(input);
    float *intensita = new float[npoints];

    int i=0;
    while(!feof(input))
    {    
        fscanf(input,"%f\n",&temp_val);
        intensita[i] = temp_val;   
        ++i;
    }

    fclose(input);

    sprintf(filename, "spettrofotometro_0.txt");

    FILE *input2 = fopen(filename, "r" );

    if(!input2)
    {
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }

    // Lettura

    float *lambda = new float[npoints];

    i=0;
    while(!feof(input))
    {    
        fscanf(input,"%f\n",&temp_val);
        lambda[i] = temp_val;   
        ++i;
    }

    fclose(input2);



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
            cout << j+1 << ":" << lambda[j] << ", " << intensita[j] << endl;
        }

    }




    // PLOT E FIT

    TCanvas *I_lambda = new TCanvas("Spettrofotometro","Spettrofotometro",200,10,1000,700);
    I_lambda->SetFillColor(0);
    I_lambda->cd();

    TGraph *gr1 = new TGraph(npoints,lambda,intensita);
    gr1->SetFillColor(4);
    

    // Abbellimenti
    gr1->SetTitle("Spettrofotometro"); // Titolo del grafico
    gr1->GetYaxis()->SetTitle("Intensità"); // Titoli degli assi
    gr1->GetXaxis()->SetTitle("Lunghezza d'onda #lambda [nm]");

    //Per impostare scala logaritmica:
    //su asse x:
    //I_lambda->SetLogx(1);
    //su asse y:
    //I_lambda->SetLogy(1);

    gr1->Draw("AB");





}
