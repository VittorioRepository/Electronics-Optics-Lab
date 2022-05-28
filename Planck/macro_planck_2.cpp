/* 

PLANCK

*/ 


void macro_planck_2()
{

    // SCELTA INIZIALE: FILE DA ANALIZZARE

    int starter = 5;
    char filename[100];

    cout << "\n\nANALISI DATI ESPERIENZA DI PLANCK\n";

    do
    {
        cout << "Quale metodo per la tensione di contro-campo vuoi analizzare?\n";
        cout << "1:  INSERISCI 1\n2:  INSERISCI 2\n3:  INSERISCI 3\n4:  INSERISCI 4\n";       
        cin >> starter;
        if (starter!=1 and starter !=2 and starter !=3 and starter !=4) cout << "Hai inserito un valore non consentito.\n";
    } while (starter!=1 and starter !=2 and starter !=3 and starter !=4);

    if (starter==1) sprintf(filename, "metodo_1.txt");
    if (starter==2) sprintf(filename, "metodo_2.txt");
    if (starter==3) sprintf(filename, "metodo_3.txt");
    if (starter==4) sprintf(filename, "metodo_4.txt");

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
    cout << "\nSono state raccolte: " << npoints << " misure di coppie Lunghezza d'onda - Tensione" << endl << endl;

    // Lettura 

    rewind(input);

    float *lambda = new float[npoints];
    float *V = new float[npoints];
    float *err_lambda = new float[npoints];
    float *err_V = new float[npoints];

    int i=0;
    while(!feof(input))
    {
        if(i<npoints){
            fscanf(input,"%f\n",&temp_val);
            lambda[i] = temp_val*1e-9;   // ATTENZIONE, HO TRASFORMATO IN METRI
            err_lambda[i] = 1;
            
        }
        else if(i<2*npoints){
            fscanf(input,"%f\n",&temp_val);
            V[i-npoints] = temp_val;
            if(V[i-npoints]<1000) err_V[i-npoints] = 0.1/100*V[i-npoints]+0.5;
            else err_V[i-npoints] = 0.1/100*V[i-npoints]+5;
            
            V[i-npoints] = V[i-npoints]/1000;
            err_V[i-npoints] = err_V[i-npoints]/1000;
        }
        ++i;
        
    }

    fclose(input);

    // Errori su V nel caso del metodo 4: calcolati tramite propagazione degli errori e inseriti qui brutalmente per fare prima

    if(starter==4)
    {
        err_V[0] = 227.7/1000;
        err_V[1] = 225.1/1000;
        err_V[2] = 80.0/1000;
    }

    // Passaggio da lambda a nu:     lambda*nu=c   

    float *nu = new float[npoints];
    float *err_nu = new float[npoints];

    float c = 299792458;
    for(int k=0; k<npoints; k++)
    {
        nu[k] = c/lambda[k];
        err_nu[k] = 1;
    }


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
            cout << j+1 << "  #nu:  " << nu[j] << " +- " << err_nu[j] << "    V:  " << V[j] << " +- " << err_V[j] << endl;
        }
    cout << endl << endl;
    }




    // PLOT E FIT

    TCanvas *V_nu = new TCanvas("Planck","Planck - 2",200,10,1000,700);
    V_nu->SetFillColor(0);
    V_nu->cd();
    TGraphErrors *g_v_nu = new TGraphErrors(npoints,nu,V,err_nu,err_V);

    // Abbellimenti 
    g_v_nu->SetMarkerSize(0.6);
    g_v_nu->SetMarkerStyle(21);
    g_v_nu->SetTitle("V(#nu)"); // Titolo del grafico
    g_v_nu->GetXaxis()->SetTitle("Frequenza #nu [Hz]"); // Titoli degli assi
    g_v_nu->GetYaxis()->SetTitle("Tensione V [V]");

    //Per impostare scala logaritmica:
    //su asse x:
    //V_nu->SetLogx(1);
    //su asse y:
    //V_nu->SetLogy(1);

    g_v_nu->Draw("AP");



    // V(\nu)

    TF1 *function = new TF1("Fit","[0]+[1]*x/(1.602176634*pow(10,-19))",0,1e17);
    
    function->SetParameter(0,0);
    function->SetParameter(1,1e-30);


    function->SetLineColor(4); // Blu
    g_v_nu->Fit(function,"RM+");
    gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph

    


}