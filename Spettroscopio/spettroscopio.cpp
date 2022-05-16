/* 

SPETTROSCOPIO

*/ 


void spettroscopio()
{
    char filename[100];

    // Scelta file
    int starter;
    do{
    cout << "\nQuale file vuoi analizzare?\n";
    cout << "Ordine +1:    inserisci 1\n";
    cout << "Ordine +2:    inserisci 2\n";
    cout << "Ordine -1:    inserisci 3\n";
    cout << "Ordine -2:    inserisci 4\n";
    cin >> starter;
    if (starter!=1 and starter!=2 and starter!=3 and starter!=4) 
        {
            cout << "VALORE INSERITO NON VALIDO" << endl;
        }
    } while (starter!=1 and starter!=2 and starter!=3 and starter!=4);

    if (starter==1) sprintf(filename, "+1.txt");
    if (starter==2) sprintf(filename, "+2.txt");
    if (starter==3) sprintf(filename, "-1.txt");
    if (starter==4) sprintf(filename, "-2.txt");

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
    g_n_lambda->SetTitle("n(#lambda)"); // Titolo del grafico
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
    
    //function->SetParameter(0,0);
    //function->SetParameter(1,0);
    //function->SetParameter(2,0);
    function->SetLineColor(4); // Blu
    g_n_lambda->Fit(function,"RM+");


    // polinomiale 

    TCanvas *n_lambda_2 = new TCanvas("Spettroscopio_2","Spettroscopio_2",200,10,1000,700);
    n_lambda_2->SetFillColor(0);
    n_lambda_2->cd();
    TGraphErrors *g_n_lambda_2 = new TGraphErrors(npoints,lambda,n,err_lambda,err_n);

    // Abbellimenti 
    g_n_lambda_2->SetMarkerSize(0.6);
    g_n_lambda_2->SetMarkerStyle(21);
    g_n_lambda_2->SetTitle("n(#lambda) polinomiale"); // Titolo del grafico
    g_n_lambda_2->GetYaxis()->SetTitle("Indice di rifrazione n"); // Titoli degli assi
    g_n_lambda_2->GetXaxis()->SetTitle("Lunghezza d'onda #lambda [nm]");
    g_n_lambda_2->Draw("AP");

    TF1 *function2 = new TF1("Fit","[0]+[1]*x+[2]*pow(x,2)",100,1000);
    
    function2->SetParameter(0,10);
    function2->SetParameter(1,-0.5e-2);
    function2->SetParameter(2,1e-16);
    function2->SetLineColor(3); // verde
    
    g_n_lambda_2->Fit(function2,"RM+");

    gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph



}