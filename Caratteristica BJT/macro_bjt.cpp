/* 

INTRODUZIONE:
La macro è suddivisa in 4 parti:
    1) Lettura dei file contenenti i dati
    2) Stampa a schermo degli array se necessario
    3) Plot
    4) Lettura e Plot Iv(Vbe)

    E' tutto dentro ad un ciclo for per accorciare di molto il codice.
    I dati vengono presi da più file ma vengono inseriti in array cumulativi.
    Attenzione all'utilizzo del contatore special_counter.

*/

using namespace std;


void macro_bjt(){

    char filename[100];
    int i=0;
    int special_counter = 0;
    int decisione_stampa = 0;


    float *I = new float[150]; // Prima di plottare bisogna però sistemare la lunghezza degli array
    float *err_I = new float[150]; 
    float *V = new float[150];
    float *err_V = new float[150];


    cout << "\n\nANALISI DATI CARATTERISTICA TRANSISTOR BJT" << endl;        

    for(int k=0; k<5; k++)
    {
        // PARTE 1: LETTURA FILE

        // Decisione Stampa
        if(k==0){
            cout << "Desideri stampare a schermo tutti i dati?\n";
            cout << "Sì: inserire 0 e premere INVIO\n";
            cout << "No: inserire 1 e premere INVIO\n";
            cin >> decisione_stampa;
        }

        // Apertura file
        if (k==0) sprintf(filename, "data_100.txt");
        else if (k==1) sprintf(filename, "data_150.txt");
        else if (k==2) sprintf(filename, "data_200.txt");
        else if (k==3) sprintf(filename, "data_250.txt");
        else if (k==4) sprintf(filename, "data_300.txt");


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


        cout << "\nRACCOLTA NUMERO" << k << ": sono state registrate: " << npoints << " coppie di valori I-V" << endl << endl;


        // Lettura del file

        rewind(input);

        i=0;
        while(!feof(input))
        {
            if(i<npoints)
            {
                fscanf(input,"%f\n",&temp_val);
                V[i+special_counter] = temp_val;
            }
            else if(i<2*npoints)
            {
                fscanf(input,"%f\n",&temp_val);
                err_V[i-npoints+special_counter] = temp_val;
            }
            else if(i<3*npoints)
            {
                fscanf(input,"%f\n",&temp_val);
                I[i-2*npoints+special_counter] = temp_val;
            }
            else if(i<4*npoints)
            {
                fscanf(input,"%f\n",&temp_val);
                err_I[i-3*npoints+special_counter] = temp_val;
            }
            ++i;
        }

        // PARTE 2: STAMPA DEI DATI

        // Stampa

        if (decisione_stampa==0){
            cout << "PRESA DATI NUMERO: " << k << endl;
            cout << "\n\nCORRENTI:\n";
            for(int i=0; i<npoints; i++){
                cout << i << ": " << I[i+special_counter] << "+-" << err_I[i+special_counter] << "mA\n";
            }
            cout << "\nTENSIONI:\n";
            for(int i=0; i<npoints; i++){
                cout << i << ": " << V[i+special_counter] << "+-" << err_V[i+special_counter] << "mV\n";
            }
        }

        cout << endl << endl;



        special_counter = special_counter + npoints; //PASSAGGIO CHIAVE 

    }
    
    // CORREZIONE LUNGHEZZA ARRAY
    
    float *I_2 = new float[special_counter];
    float *err_I_2 = new float[special_counter];
    float *V_2 = new float[special_counter];
    float *err_V_2 = new float[special_counter];

    for(int n=0; n<special_counter; n++)
    {
        I_2[n]=I[n];
        err_I_2[n]=err_I[n];
        V_2[n]=V[n];
        err_V_2[n]=err_V[n];
    } 

    

    // PARTE 3: PLOT E FIT

    TCanvas *iv = new TCanvas("TRANSISTOR Ic(Vce)","Transistor BJT",200,10,1000,700);
    iv->SetFillColor(0);
    iv->cd();

    TGraphErrors *giv = new TGraphErrors(special_counter,V_2,I_2,err_V_2,err_I_2);
    giv->SetMarkerSize(0.6);
    giv->SetMarkerStyle(21);
    giv->SetTitle("Ic(Vce)"); // Titolo del grafico
    giv->GetYaxis()->SetTitle("Corrente I [mA]"); // Titoli degli assi
    giv->GetXaxis()->SetTitle("Tensione [mV]");
    giv->Draw("AP");
    




    // Parte 4: Ib(Vbe)

    float *Ib = new float[special_counter];
    float *err_Ib = new float[special_counter];
    float *Vbe = new float[special_counter];
    float *err_Vbe = new float[special_counter];
    
    sprintf(filename, "data_Ib_Vbe.txt");
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


        cout << "\nSono state registrate: " << npoints/3 << " coppie di valori I-V per ogni valore fissato di Ic" << endl << endl;


        // Lettura del file

        rewind(input);

        i=0;
        while(!feof(input))
        {
            if(i<npoints)
            {
                fscanf(input,"%f\n",&temp_val);
                Vbe[i] = temp_val;
            }
            else if(i<2*npoints)
            {
                fscanf(input,"%f\n",&temp_val);
                err_Vbe[i-npoints] = temp_val;
            }
            else if(i<3*npoints)
            {
                fscanf(input,"%f\n",&temp_val);
                Ib[i-2*npoints] = temp_val;
            }
            else if(i<4*npoints)
            {
                fscanf(input,"%f\n",&temp_val);
                err_Ib[i-3*npoints] = temp_val;
            }
            ++i;
        }

        // stampa 

        if (decisione_stampa==0){
            cout << "DATI Ib(Vbe): " << endl;
            cout << "\n\nCORRENTI:\n";
            for(int i=0; i<npoints; i++){
                cout << i << ": " << Ib[i+special_counter] << "+-" << err_Ib[i+special_counter] << "mA\n";
            }
            cout << "\nTENSIONI:\n";
            for(int i=0; i<npoints; i++){
                cout << i << ": " << Vbe[i+special_counter] << "+-" << err_Vbe[i+special_counter] << "mV\n";
            }
        }

        cout << endl << endl;

        // Plot e FIt

        TCanvas *iv_2 = new TCanvas("TRANSISTOR Ib(Vbe)","Transistor BJT",200,10,1000,700);
        iv_2->SetFillColor(0);
        iv_2->cd();

        TGraphErrors *giv_2 = new TGraphErrors(npoints,Vbe,Ib,err_Vbe,err_Ib);
        giv_2->SetMarkerSize(0.6);
        giv_2->SetMarkerStyle(21);
        giv_2->SetTitle("Ib(Vbe)"); // Titolo del grafico
        giv_2->GetYaxis()->SetTitle("Corrente I [mA]"); // Titoli degli assi
        giv_2->GetXaxis()->SetTitle("Tensione [mV]");
        giv_2->Draw("AP");


}