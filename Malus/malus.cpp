/* 

MALUS

*/ 


void malus()
{
    char filename[100];
    sprintf(filename, "malus.txt");

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
    cout << "\nSono state raccolte: " << npoints << " misure di coppie intensità - angolo" << endl;

    // Lettura 

    rewind(input);
    float *I = new float[npoints];
    float *theta = new float[npoints];
    float *err_I = new float[npoints];
    float *err_theta = new float[npoints];

    int i=0;
    while(!feof(input))
    {
        if(i<npoints){
            fscanf(input,"%f\n",&temp_val);
            theta[i] = temp_val;
            err_theta[i] = 1;
        }
        else if(i<2*npoints){
            fscanf(input,"%f\n",&temp_val);
            I[i-npoints] = temp_val;
            err_I[i-npoints] = I[i-npoints]*(0.5/100)+0.1;
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
        for(int j=0;j<npoints-1;j++){
            cout << theta[j] << ": " << I[j] << " +- " << err_I[j] << endl;
        }

    }




    // PLOT E FIT

    TCanvas *I_theta = new TCanvas("Malus","Malus",200,10,1000,700);
    I_theta->SetFillColor(0);
    I_theta->cd();
    TGraphErrors *g_it = new TGraphErrors(npoints,theta,I,err_theta,err_I);

    // Abbellimenti 
    g_it->SetMarkerSize(0.6);
    g_it->SetMarkerStyle(21);
    g_it->SetTitle("I(#theta)"); // Titolo del grafico
    g_it->GetYaxis()->SetTitle("Corrente I [#mu A]"); // Titoli degli assi
    g_it->GetXaxis()->SetTitle("Angolo #theta");

    //Per impostare scala logaritmica:
    //su asse x:
    //I_theta->SetLogx(1);
    //su asse y:
    //I_theta->SetLogy(1);

    g_it->Draw("AP");



    // I(theta)   

    TF1 *function = new TF1("Fit","[0]+[1]*pow(cos(x/180*3.1415926535+[2]),2)",-5,375);
    
    //function->SetParameter(0,0);
    //function->SetParameter(1,0);
    //function->SetParameter(2,0);


    function->SetLineColor(4); // Blu
    g_it->Fit(function,"RM+");
    gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph



}