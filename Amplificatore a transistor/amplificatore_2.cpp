/* 

AMPLIFICATORE 2

*/ 


void amplificatore_2()
{
    // SCELTA INIZIALE 

    int starter = 5;
    char filename[100];

    cout << "\n\nANALISI DATI POLARIMETRO\n";

    do
    {
        cout << "Quale set di dati vuoi analizzare?\n";
        cout << "beta:   INSERISCI 0\nAv:         INSERISCI 1\n";       
        cin >> starter;
        if (starter!=0 and starter !=1) cout << "Hai inserito un valore non consentito.\n";
    } while (starter!=0 and starter !=1);

    if (starter==0) sprintf(filename, "beta.txt");
    if (starter==1) sprintf(filename, "Av.txt");

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

    npoints = npoints/4;
    cout << "\nSono state raccolte: " << npoints << " coppie di misure" << endl;

    // Lettura 

    rewind(input);
    float *y = new float[npoints];
    float *err_y = new float[npoints];
    float *x = new float[npoints];
    float *err_x = new float[npoints];

    int i=0;
    while(!feof(input))
    {
        if(i<npoints){
            fscanf(input,"%f\n",&temp_val);
            y[i] = temp_val;
        }
        else if(i<2*npoints){
            fscanf(input,"%f\n",&temp_val);
            err_y[i-npoints] = temp_val;
        }
        else if(i<3*npoints){
            fscanf(input,"%f\n",&temp_val);
            x[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints){
            fscanf(input,"%f\n",&temp_val);
            err_x[i-3*npoints] = temp_val;
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
            cout << x[j] << " +- " << err_x[j] << " : " << y[j] << " +- " << err_y[j] << endl;
        }

    }




    // PLOT E FIT

    TCanvas *can = new TCanvas("Amplificatore","Amplificatore a Trasnsistor",200,10,1000,700);
    can->SetFillColor(0);
    can->cd();
    TGraphErrors *gyx = new TGraphErrors(npoints,x,y,err_x,err_y);

    // Abbellimenti 
    gyx->SetMarkerSize(0.9);
    gyx->SetMarkerColor(2);
    gyx->SetMarkerStyle(21);
    gyx->SetTitle("Vout(Vin)"); // Titolo del grafico
    gyx->GetYaxis()->SetTitle("Vout"); // Titoli degli assi
    gyx->GetXaxis()->SetTitle("Vin");

    //Per impostare scala logaritmica:
    //su asse x:
    //can->SetLogx(1);
    //su asse y:
    //can->SetLogy(1);

    gyx->Draw("AP");

 

    TF1 *function = new TF1("Fit","[0]+[1]*x",0,1e4);
    
    
    function->SetParameter(0,0);
    function->SetParameter(1,0);


    function->SetLineColor(4); // Blu
    gyx->Fit(function,"RM+");
    gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph



}