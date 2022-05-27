/* 

PLANCK

*/ 


void macro_planck_1()
{

    // SCELTA INIZIALE: FILE DA ANALIZZARE

    int starter = 5;
    char filename[100];

    cout << "\n\nANALISI DATI ESPERIENZA DI PLANCK\n";

    do
    {
        cout << "Quale set di dati vuoi analizzare?\n";
        cout << "1:  INSERISCI 1\n2:  INSERISCI 2\n3:  INSERISCI 3\n4:  INSERISCI 4\n";       
        cin >> starter;
        if (starter!=1 and starter !=2 and starter !=3 and starter!=4) cout << "Hai inserito un valore non consentito.\n";
    } while (starter!=1 and starter !=2 and starter !=3 and starter!=4);

    if (starter==1) sprintf(filename, "data_1.txt");
    if (starter==2) sprintf(filename, "data_2.txt");
    if (starter==3) sprintf(filename, "data_3.txt");
    if (starter==4) sprintf(filename, "data_4.txt");

    cout << "\nHai scelto di analizzare: " << filename << endl;



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

    npoints = npoints/2;
    cout << "\nSono state raccolte: " << npoints << " misure di coppie Tensione - Corrente" << endl;

    // Lettura 

    rewind(input);

    float *I = new float[npoints];
    float *V = new float[npoints];
    float *err_I = new float[npoints];
    float *err_V = new float[npoints];

    int i=0;
    while(!feof(input))
    {
        if(i<npoints){
            fscanf(input,"%f\n",&temp_val);
            V[i] = temp_val;
            if(V[i]<1000) err_V[i] = 0.1/100*V[i]+0.5;
            else err_V[i] = 0.1/100*V[i]+5;
        }
        else if(i<2*npoints){
            fscanf(input,"%f\n",&temp_val);
            I[i-npoints] = temp_val;
            err_I[i-npoints] = 0.4/100*I[i-npoints]+400e-6;    // 0.4% +- 400 fA (siamo in nanoAmpere)
        }
        ++i;
        
    }

    fclose(input);



    // Stampa dei valori
    
    int stampa = 5;

    do
    {
        cout << "Vuoi stampare i valori raccolti a schermo?\nSI:   INSERISCI 0\nNO:   INSERISCI 1\n";
        cin >> stampa;
        if (stampa!=0 and stampa!=1) cout << "Hai inserito un valore non consentito.\n";
    } while (stampa!=0 and stampa!=1);

    if (stampa==0)
    {
        cout << "VALORI" << endl;
        for(int j=0;j<npoints;j++){
            cout << "Misura numero " << j+1 << "  V:  " << V[j] << " +- " << err_V[j] << "  I:  " << I[j] << " +- " << err_I[j] << endl;
        }
    cout << endl << endl;
    }




    // PLOT E FIT

    TCanvas *I_V = new TCanvas("Planck","Planck",200,10,1000,700);
    I_V->SetFillColor(0);
    I_V->cd();
    TGraphErrors *g_iv = new TGraphErrors(npoints,V,I,err_V,err_I);

    // Abbellimenti 
    g_iv->SetMarkerSize(0.6);
    g_iv->SetMarkerStyle(21);
    g_iv->SetTitle("I(V)"); // Titolo del grafico
    g_iv->GetYaxis()->SetTitle("Corrente I [nA]"); // Titoli degli assi
    g_iv->GetXaxis()->SetTitle("Tensione V [mV]");

    //Per impostare scala logaritmica:
    //su asse x:
    //I_V->SetLogx(1);
    //su asse y:
    //I_V->SetLogy(1);

    g_iv->Draw("AP");



    // I(V)    1

    TF1 *function = new TF1("Fit","[0]",850,4000);
    
    //function->SetParameter(0,0);
    //function->SetParameter(1,0);
    //function->SetParameter(2,0);


    function->SetLineColor(4); // Blu
    g_iv->Fit(function,"RM+");
    gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph

    


}