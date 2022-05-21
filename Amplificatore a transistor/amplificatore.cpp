/* 

AMPLIFICATORE

*/ 


void amplificatore()
{
    char filename[100];
    sprintf(filename, "data.txt");

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

    npoints = npoints/3;
    cout << "\nSono state raccolte: " << npoints << " misure di coppie guadagno - frequenza" << endl;

    // Lettura 

    rewind(input);
    float *f = new float[npoints];
    float *err_f = new float[npoints];
    float *Av = new float[npoints];
    float *err_Av = new float[npoints];

    int i=0;
    while(!feof(input))
    {
        if(i<npoints){
            fscanf(input,"%f\n",&temp_val);
            f[i] = temp_val;
            err_f[i] = 1/1000*f[i];
        }
        else if(i<2*npoints){
            fscanf(input,"%f\n",&temp_val);
            Av[i-npoints] = temp_val;
        }
        else if(i<3*npoints){
            fscanf(input,"%f\n",&temp_val);
            err_Av[i-2*npoints] = temp_val;
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
            cout << f[j] << " +- " << err_f[j] << " : " << Av[j] << " +- " << err_Av[j] << endl;
        }

    }




    // PLOT E FIT

    TCanvas *I_theta = new TCanvas("Amplificatore","Amplificatore a Trasnsistor",200,10,1000,700);
    I_theta->SetFillColor(0);
    I_theta->cd();
    TGraphErrors *g_it = new TGraphErrors(npoints,f,Av,err_f,err_Av);

    // Abbellimenti 
    g_it->SetMarkerSize(0.6);
    g_it->SetMarkerStyle(21);
    g_it->SetTitle("Av(f)"); // Titolo del grafico
    g_it->GetYaxis()->SetTitle("Guadagno Av"); // Titoli degli assi
    g_it->GetXaxis()->SetTitle("Frequenza [Hz]");

    //Per impostare scala logaritmica:
    //su asse x:
    I_theta->SetLogx(1);
    //su asse y:
    //I_theta->SetLogy(1);

    g_it->Draw("AP");



    // I(theta)   

    TF1 *function = new TF1("Fit","[0]+[1]*pow(x-[2],-1)+[3]*pow(x-[2],-2)",0,1e7);
    
    //function->SetParameter(0,0);
    //function->SetParameter(1,0);
    //function->SetParameter(2,0);


    function->SetLineColor(4); // Blu
    g_it->Fit(function,"RM+");
    gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph



}