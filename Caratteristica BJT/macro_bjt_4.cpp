/* 

BJT PARTE 3

*/

using namespace std;


void macro_bjt_4(){

    char filename[100];
    int decisione_stampa = 0;


    cout << "\n\nANALISI DATI CARATTERISTICA TRANSISTOR BJT" << endl;        

    // PARTE 1: LETTURA FILE

    // Scelta file
    int starter=0;
    do{
    cout << "\nQuale file vuoi analizzare?\n";
    cout << "100 mA:    inserisci 1\n";
    cout << "150 mA:    inserisci 2\n";
    cout << "200 mA:    inserisci 3\n";
    cout << "250 mA:    inserisci 4\n";
    cout << "300 mA:    inserisci 5\n";
    cin >> starter;
    if (starter!=1 && starter!=2 && starter!=3 && starter!=4 && starter!=5)
        {
            cout << "VALORE INSERITO NON VALIDO" << endl;
        }
    } while (starter!=1 && starter!=2 && starter!=3 && starter!=4 && starter!=5);

    if (starter==1) sprintf(filename, "data_100.txt");
    if (starter==2) sprintf(filename, "data_150.txt");
    if (starter==3) sprintf(filename, "data_200.txt");
    if (starter==4) sprintf(filename, "data_250.txt");
    if (starter==5) sprintf(filename, "data_300.txt");

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
    giv->SetMarkerSize(0.8);
    giv->SetMarkerColor(2);
    giv->SetMarkerStyle(21);
    giv->SetTitle("Ic(Vce)"); // Titolo del grafico
    giv->GetYaxis()->SetTitle("Corrente I [mA]"); // Titoli degli assi
    giv->GetXaxis()->SetTitle("Tensione V [V]");
    giv->Draw("AP");



    




}
