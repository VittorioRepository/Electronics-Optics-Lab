/* 

BJT PARTE 3

*/

using namespace std;


void macro_bjt_6(){

    char filename[100];
    int decisione_stampa = 0;


    cout << "\n\nANALISI DATI CARATTERISTICA TRANSISTOR BJT" << endl;        

    // FILE 1
    // PARTE 1: LETTURA FILE

    sprintf(filename, "Ib_Vbe_1.txt");

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


    float *Ib = new float[npoints];
    float *err_Ib = new float[npoints]; 
    float *Vbe = new float[npoints];
    float *err_Vbe = new float[npoints];



    cout << "\nSono state registrate: " << npoints << " coppie di valori fattore di corrente - tensione" << endl << endl;


    // Lettura del file

    rewind(input);

    int i=0;
    while(!feof(input))
    {
        if(i<npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Ib[i] = temp_val;
        }
        else if(i<2*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Ib[i-npoints] = temp_val;
        }
        else if(i<3*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Vbe[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Vbe[i-3*npoints] = temp_val;
        }
        ++i;
    }

    // PARTE 3: GRAPH

    TGraphErrors *giv = new TGraphErrors(npoints,Vbe,Ib,err_Vbe,err_Ib);
    giv->SetMarkerSize(0.7);
    giv->SetMarkerStyle(21);
    giv->SetMarkerColor(2);

    // FILE 1
    // PARTE 1: LETTURA FILE

    sprintf(filename, "Ib_Vbe_2.txt");

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


    float *Ib2 = new float[npoints];
    float *err_Ib2 = new float[npoints]; 
    float *Vbe2 = new float[npoints];
    float *err_Vbe2 = new float[npoints];



    cout << "\nSono state registrate: " << npoints << " coppie di valori fattore di corrente - tensione" << endl << endl;


    // Lettura del file

    rewind(input);

    i=0;
    while(!feof(input))
    {
        if(i<npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Ib2[i] = temp_val;
        }
        else if(i<2*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Ib2[i-npoints] = temp_val;
        }
        else if(i<3*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Vbe2[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Vbe2[i-3*npoints] = temp_val;
        }
        ++i;
    }

    // PARTE 3: GRAPH

    TGraphErrors *giv2 = new TGraphErrors(npoints,Vbe2,Ib2,err_Vbe2,err_Ib2);
    giv2->SetMarkerSize(0.7);
    giv2->SetMarkerStyle(21);
    giv2->SetMarkerColor(2);

// FILE 1
    // PARTE 1: LETTURA FILE

    sprintf(filename, "Ib_Vbe_3.txt");

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


    float *Ib3 = new float[npoints];
    float *err_Ib3 = new float[npoints]; 
    float *Vbe3 = new float[npoints];
    float *err_Vbe3 = new float[npoints];



    cout << "\nSono state registrate: " << npoints << " coppie di valori fattore di corrente - tensione" << endl << endl;


    // Lettura del file

    rewind(input);

    i=0;
    while(!feof(input))
    {
        if(i<npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Ib3[i] = temp_val;
        }
        else if(i<2*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Ib3[i-npoints] = temp_val;
        }
        else if(i<3*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            Vbe3[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_Vbe3[i-3*npoints] = temp_val;
        }
        ++i;
    }

    // PARTE 3: GRAPH

    TGraphErrors *giv3 = new TGraphErrors(npoints,Vbe3,Ib3,err_Vbe3,err_Ib3);
    giv3->SetMarkerSize(0.7);
    giv3->SetMarkerStyle(21);
    giv3->SetMarkerColor(2);







    TCanvas *iv = new TCanvas("TRANSISTOR Ib(Vbe)","Transistor BJT",200,10,1000,700);
    iv->SetFillColor(0);
    iv->cd();
    TMultiGraph *mg = new TMultiGraph();
    mg->SetTitle("Ib(Vbe)"); // Titolo del grafico
    mg->GetYaxis()->SetTitle("Corrente I [mA]"); // Titoli degli assi
    mg->GetXaxis()->SetTitle("Tensione V [V]");
                                                                           // PER ZOOM
    TF1 *function_1 = new TF1("Fit","[0]*(exp(x/([1]*26))-1)",0,3);  //0.56,0.62
    TF1 *function_2 = new TF1("Fit","[0]*(exp(x/([1]*26))-1)",0,3);  //0.56,0.61
    TF1 *function_3 = new TF1("Fit","[0]*(exp(x/([1]*26))-1)",0,3);  //0.56,0.595

    function_1->SetParameter(0,1e-6);
    function_2->SetParameter(0,1e-10);
    function_3->SetParameter(0,1e-7);
    
    function_1->SetParameter(1,1.5);
    function_2->SetParameter(1,1.5);
    function_3->SetParameter(1,1.5);

    function_1->SetLineColor(4); // Blu
    function_2->SetLineColor(4); // Blu
    function_3->SetLineColor(4); // Blu

    giv->Fit(function_1,"RM+");
    giv2->Fit(function_2,"RM+");
    giv3->Fit(function_3,"RM+");

    gStyle->SetOptFit(0); //print the information on fit parameters results in the statistics box directly on the TGraph

    mg->Add(giv);
    mg->Add(giv2);
    mg->Add(giv3);

    mg->Draw("AP");





}
