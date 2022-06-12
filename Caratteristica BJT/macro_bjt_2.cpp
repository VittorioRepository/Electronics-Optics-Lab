/* 

BJT PARTE 2

*/

using namespace std;


void macro_bjt_2(){

    char filename[100];
    int decisione_stampa = 0;


    cout << "\n\nANALISI DATI CARATTERISTICA TRANSISTOR BJT" << endl;        

    // PARTE 1: LETTURA FILE

    // Decisione Stampa
        cout << "Desideri stampare a schermo tutti i dati?\n";
        cout << "Sì: inserire 0 e premere INVIO\n";
        cout << "No: inserire 1 e premere INVIO\n";
        cin >> decisione_stampa;

    // Decisione Fit
        cout << "\n\nVuoi fare un fit?\n";
        cout << "SI, con parabola:          inserisci 0\nSI, con funzione strana:   inserisci 1\nNO:                        inserisci 2\n";
        int decisione_fit = 2;
        cin >> decisione_fit;


    // Apertura file
    sprintf(filename, "data_b_Ic.txt");


    FILE *input = fopen(filename, "r" );

    if(!input)
    {
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }

    // Numero di dati raccolti

    float temp_val;

    int npoints = 0;

    while(!feof(input))
    {
        fscanf(input,"%f\n",&temp_val);
        ++npoints;
    }

    npoints = npoints/4;


    float *I = new float[npoints];
    float *err_I = new float[npoints]; 
    float *b = new float[npoints];
    float *err_b = new float[npoints];



    cout << "\nSono state registrate: " << npoints << " coppie di valori fattore di amplificazione - corrente" << endl << endl;


    // Lettura del file

    rewind(input);

    int i=0;
    while(!feof(input))
    {
        if(i<npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            I[i] = temp_val;
        }
        else if(i<2*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_I[i-npoints] = temp_val;
        }
        else if(i<3*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            b[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_b[i-3*npoints] = temp_val;
        }
        ++i;
    }

    // PARTE 2: STAMPA DEI DATI

    // Stampa

    if (decisione_stampa==0){
        cout << "\n\nSTAMPA DATI RACCOLTI:\n";
        cout << "\nFATTORI DI AMPLIFICAZIONE:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << b[i] << "+-" << err_b[i] << " mA\n";
        }
        cout << "\nCORRENTI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << I[i] << "+-" << err_I[i] << " mV\n";
        }
    }

    cout << endl << endl;



    // PARTE 3: PLOT E FIT

    TCanvas *bi = new TCanvas("TRANSISTOR Ic(Vce)","Transistor BJT",200,10,1000,700);
    bi->SetFillColor(0);
    bi->cd();

    TGraphErrors *gib = new TGraphErrors(npoints,I,b,err_I,err_b);
    gib->SetMarkerSize(0.8);
    gib->SetMarkerColor(2);
    gib->SetMarkerStyle(21);
    gib->SetTitle("#beta(Ib)"); // Titolo del grafico
    gib->GetYaxis()->SetTitle("Fattore #beta"); // Titoli degli assi
    gib->GetXaxis()->SetTitle("Corrente [mA]");
    gib->Draw("AP");

    if (decisione_fit==0){
        TF1 *function_1 = new TF1("Fit","[0]+[1]*x+[2]*pow(x,2)",0,1000);
            
        function_1->SetParameter(0,0);
        function_1->SetParameter(1,10);

        function_1->SetLineColor(4); // Blu
        gib->Fit(function_1,"RM+");
        gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph
    }

    if (decisione_fit==1){
        TF1 *function_1 = new TF1("Fit","[0]*(1-exp(-x/[1]))",0,1000);
            
        function_1->SetParameter(0,0);
        function_1->SetParameter(1,10);

        function_1->SetLineColor(4); // Blu
        gib->Fit(function_1,"RM+");
        gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph
    }
    




}
