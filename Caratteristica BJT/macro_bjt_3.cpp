/* 

BJT PARTE 3

*/

using namespace std;


void macro_bjt_3(){

    char filename[100];
    int decisione_stampa = 0;


    cout << "\n\nANALISI DATI CARATTERISTICA TRANSISTOR BJT" << endl;        

    // PARTE 1: LETTURA FILE

    // Scelta file
    int starter=0;
    do{
    cout << "\nQuale file vuoi analizzare?\n";
    cout << "1:    inserisci 1\n";
    cout << "2:    inserisci 2\n";
    cout << "3:    inserisci 3\n";
    cin >> starter;
    if (starter!=1 && starter!=2 && starter!=3)
        {
            cout << "VALORE INSERITO NON VALIDO" << endl;
        }
    } while (starter!=1 && starter!=2 && starter!=3);

    if (starter==1) sprintf(filename, "Ib_Vbe_1.txt");
    if (starter==2) sprintf(filename, "Ib_Vbe_2.txt");
    if (starter==3) sprintf(filename, "Ib_Vbe_3.txt");

    // Decisione Stampa
    cout << "Desideri stampare a schermo tutti i dati?\n";
    cout << "Sì: inserire 0 e premere INVIO\n";
    cout << "No: inserire 1 e premere INVIO\n";
    cin >> decisione_stampa;



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

    // PARTE 2: STAMPA DEI DATI

    // Stampa

    if (decisione_stampa==0){
        cout << "\n\nSTAMPA DATI RACCOLTI:\n";
        cout << "\nCORRENTI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << Ib[i] << "+-" << err_Ib[i] << " mA\n";
        }
        cout << "\nTENSIONI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << Vbe[i] << "+-" << err_Vbe[i] << " mV\n";
        }
    }

    cout << endl << endl;



    // PARTE 3: PLOT E FIT

    TCanvas *iv = new TCanvas("TRANSISTOR Ib(Vbe)","Transistor BJT",200,10,1000,700);
    iv->SetFillColor(0);
    iv->cd();

    TGraphErrors *giv = new TGraphErrors(npoints,Vbe,Ib,err_Vbe,err_Ib);
    giv->SetMarkerSize(0.6);
    giv->SetMarkerStyle(21);
    giv->SetTitle("Ib(Vbe)"); // Titolo del grafico
    giv->GetYaxis()->SetTitle("Corrente I [mA]"); // Titoli degli assi
    giv->GetXaxis()->SetTitle("Tensione V [V]");
    giv->Draw("AP");

    TF1 *function_1 = new TF1("Fit","[0]*(exp(x/([1]*26))-1)",0,1000);

    if(starter==1) function_1->SetParameter(0,1e-6);
    if(starter==2) function_1->SetParameter(0,1e-10);
    if(starter==3) function_1->SetParameter(0,1e-7);
    
    function_1->SetParameter(1,1.5);

    function_1->SetLineColor(4); // Blu
    giv->Fit(function_1,"RM+");
    gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph


    




}
