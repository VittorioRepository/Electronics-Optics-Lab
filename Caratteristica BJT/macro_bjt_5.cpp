/* 

BJT PARTE 3

*/

using namespace std;


void macro_bjt_5(){

    char filename[100];
    int decisione_stampa = 0;


    cout << "\n\nANALISI DATI CARATTERISTICA TRANSISTOR BJT" << endl;        
    // Decisione Stampa
    cout << "Desideri stampare a schermo tutti i dati?\n";
    cout << "Sì: inserire 0 e premere INVIO\n";
    cout << "No: inserire 1 e premere INVIO\n";
    cin >> decisione_stampa;

    // FILE 1

    // PARTE 1: LETTURA FILE

    // Scelta file

    sprintf(filename, "data_100.txt");
    
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


    float *Ic = new float[npoints];
    float *err_Ic = new float[npoints]; 
    float *Vce = new float[npoints];
    float *err_Vce = new float[npoints];



    cout << "\nSono state registrate: " << npoints << " coppie di valori fattore di corrente - tensione" << endl << endl;


    // Lettura del file

    rewind(input);

    int i=0;
    while(!feof(input))
    {
        if(i<npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Vce[i] = temp_val;
        }
        else if(i<2*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Vce[i-npoints] = temp_val;
        }
        else if(i<3*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Ic[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Ic[i-3*npoints] = temp_val;
        }
        ++i;
    }

    // PARTE 2: STAMPA DEI DATI

    // Stampa

    if (decisione_stampa==0){
        cout << "\n\nSTAMPA DATI RACCOLTI:\n";
        cout << "\nCORRENTI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << Ic[i] << "+-" << err_Ic[i] << " mA\n";
        }
        cout << "\nTENSIONI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << Vce[i] << "+-" << err_Vce[i] << " mV\n";
        }
    }

    cout << endl << endl;



    // PARTE 3: PLOT E FIT

    TCanvas *iv = new TCanvas("TRANSISTOR Ic(Vce)","Transistor BJT",200,10,1000,700);
    iv->SetFillColor(0);
    iv->cd();

    TGraphErrors *giv = new TGraphErrors(npoints,Vce,Ic,err_Vce,err_Ic);
    giv->SetMarkerSize(0.7);
    giv->SetMarkerColor(2);
    giv->SetMarkerStyle(21);

    
    // FILE 2
    
    // PARTE 1: LETTURA FILE

    // Scelta file


    sprintf(filename, "data_150.txt");
    
    input = fopen(filename, "r" );

    if(!input)
    {
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }

    // Numero di dati raccolti



    npoints = 0;

    while(!feof(input))
    {
        fscanf(input,"%f\n",&temp_val);
        ++npoints;
    }

    npoints = npoints/4;


    float *Ic2 = new float[npoints];
    float *err_Ic2 = new float[npoints]; 
    float *Vce2 = new float[npoints];
    float *err_Vce2 = new float[npoints];



    cout << "\nSono state registrate: " << npoints << " coppie di valori fattore di corrente - tensione" << endl << endl;


    // Lettura del file

    rewind(input);

    i=0;
    while(!feof(input))
    {
        if(i<npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Vce2[i] = temp_val;
        }
        else if(i<2*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Vce2[i-npoints] = temp_val;
        }
        else if(i<3*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Ic2[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Ic2[i-3*npoints] = temp_val;
        }
        ++i;
    }

    // PARTE 2: STAMPA DEI DATI

    // Stampa

    if (decisione_stampa==0){
        cout << "\n\nSTAMPA DATI RACCOLTI:\n";
        cout << "\nCORRENTI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << Ic2[i] << "+-" << err_Ic2[i] << " mA\n";
        }
        cout << "\nTENSIONI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << Vce2[i] << "+-" << err_Vce2[i] << " mV\n";
        }
    }

    cout << endl << endl;



    // PARTE 3: PLOT E FIT

    TGraphErrors *giv2 = new TGraphErrors(npoints,Vce2,Ic2,err_Vce2,err_Ic2);
    giv2->SetMarkerSize(0.7);
    giv2->SetMarkerColor(2);
    giv2->SetMarkerStyle(21);


    // FILE 3
    
    // PARTE 1: LETTURA FILE

    // Scelta file
   

    sprintf(filename, "data_200.txt");
    
    input = fopen(filename, "r" );

    if(!input)
    {
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }

    // Numero di dati raccolti



    npoints = 0;

    while(!feof(input))
    {
        fscanf(input,"%f\n",&temp_val);
        ++npoints;
    }

    npoints = npoints/4;


    float *Ic3 = new float[npoints];
    float *err_Ic3 = new float[npoints]; 
    float *Vce3 = new float[npoints];
    float *err_Vce3 = new float[npoints];



    cout << "\nSono state registrate: " << npoints << " coppie di valori fattore di corrente - tensione" << endl << endl;


    // Lettura del file

    rewind(input);

    i=0;
    while(!feof(input))
    {
        if(i<npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Vce3[i] = temp_val;
        }
        else if(i<2*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Vce3[i-npoints] = temp_val;
        }
        else if(i<3*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Ic3[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Ic3[i-3*npoints] = temp_val;
        }
        ++i;
    }

    // PARTE 2: STAMPA DEI DATI

    // Stampa

    if (decisione_stampa==0){
        cout << "\n\nSTAMPA DATI RACCOLTI:\n";
        cout << "\nCORRENTI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << Ic3[i] << "+-" << err_Ic3[i] << " mA\n";
        }
        cout << "\nTENSIONI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << Vce3[i] << "+-" << err_Vce3[i] << " mV\n";
        }
    }

    cout << endl << endl;



    // PARTE 3: PLOT E FIT

    TGraphErrors *giv3 = new TGraphErrors(npoints,Vce3,Ic3,err_Vce3,err_Ic3);
    giv3->SetMarkerSize(0.7);
    giv3->SetMarkerColor(2);
    giv3->SetMarkerStyle(21);



    // FILE 4
    
    // PARTE 1: LETTURA FILE

    // Scelta file

    sprintf(filename, "data_250.txt");
    
    input = fopen(filename, "r" );

    if(!input)
    {
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }

    // Numero di dati raccolti
    
    npoints = 0;

    while(!feof(input))
    {
        fscanf(input,"%f\n",&temp_val);
        ++npoints;
    }

    npoints = npoints/4;


    float *Ic4 = new float[npoints];
    float *err_Ic4 = new float[npoints]; 
    float *Vce4 = new float[npoints];
    float *err_Vce4 = new float[npoints];



    cout << "\nSono state registrate: " << npoints << " coppie di valori fattore di corrente - tensione" << endl << endl;


    // Lettura del file

    rewind(input);

    i=0;
    while(!feof(input))
    {
        if(i<npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Vce4[i] = temp_val;
        }
        else if(i<2*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Vce4[i-npoints] = temp_val;
        }
        else if(i<3*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Ic4[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Ic4[i-3*npoints] = temp_val;
        }
        ++i;
    }

    // PARTE 2: STAMPA DEI DATI

    // Stampa

    if (decisione_stampa==0){
        cout << "\n\nSTAMPA DATI RACCOLTI:\n";
        cout << "\nCORRENTI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << Ic4[i] << "+-" << err_Ic4[i] << " mA\n";
        }
        cout << "\nTENSIONI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << Vce4[i] << "+-" << err_Vce4[i] << " mV\n";
        }
    }

    cout << endl << endl;



    // PARTE 3: PLOT E FIT

    TGraphErrors *giv4 = new TGraphErrors(npoints,Vce4,Ic4,err_Vce4,err_Ic4);
    giv4->SetMarkerSize(0.7);
    giv4->SetMarkerColor(2);
    giv4->SetMarkerStyle(21);



    // FILE 5
    
    // PARTE 1: LETTURA FILE

    // Scelta file
    

    sprintf(filename, "data_300.txt");
    
    input = fopen(filename, "r" );

    if(!input)
    {
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }

    // Numero di dati raccolti

    npoints = 0;

    while(!feof(input))
    {
        fscanf(input,"%f\n",&temp_val);
        ++npoints;
    }

    npoints = npoints/4;


    float *Ic5 = new float[npoints];
    float *err_Ic5 = new float[npoints]; 
    float *Vce5 = new float[npoints];
    float *err_Vce5 = new float[npoints];



    cout << "\nSono state registrate: " << npoints << " coppie di valori fattore di corrente - tensione" << endl << endl;


    // Lettura del file

    rewind(input);

    i=0;
    while(!feof(input))
    {
        if(i<npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Vce5[i] = temp_val;
        }
        else if(i<2*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Vce5[i-npoints] = temp_val;
        }
        else if(i<3*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Ic5[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Ic5[i-3*npoints] = temp_val;
        }
        ++i;
    }

    // PARTE 2: STAMPA DEI DATI

    // Stampa

    if (decisione_stampa==0){
        cout << "\n\nSTAMPA DATI RACCOLTI:\n";
        cout << "\nCORRENTI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << Ic5[i] << "+-" << err_Ic5[i] << " mA\n";
        }
        cout << "\nTENSIONI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << Vce5[i] << "+-" << err_Vce5[i] << " mV\n";
        }
    }

    cout << endl << endl;



    // PARTE 3: PLOT E FIT

    TGraphErrors *giv5 = new TGraphErrors(npoints,Vce5,Ic5,err_Vce5,err_Ic5);
    giv5->SetMarkerSize(0.7);
    giv5->SetMarkerColor(2);
    giv5->SetMarkerStyle(21);
    



    
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(giv);
    mg->Add(giv2);
    mg->Add(giv3);
    mg->Add(giv4);
    mg->Add(giv5);
    mg->SetTitle("Ic(Vce)"); // Titolo del grafico
    mg->GetYaxis()->SetTitle("Corrente I [mA]"); // Titoli degli assi
    mg->GetXaxis()->SetTitle("Tensione V [V]");
    mg->Draw("ALP");


    




}
