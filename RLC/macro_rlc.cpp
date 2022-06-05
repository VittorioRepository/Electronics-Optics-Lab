/* 

INTRODUZIONE:
La macro è suddivisa in 5 parti:
    1) Lettura del file contenenti i dati
    2) Elaborazione dei dati per ottenere tutte le grandezze necessarie all'analisi e i rispettivi errori
    3) Stampa a schermo degli array se necessario
    4) Plot e Fit del guadagno in funzione della frequenza. Determinazione della frequenza di risonanza. (filtro passa-banda)

    Nella parte 1 è stato implementato un sistema che permette di scegliere da terminale quale file dati far leggere al programma. 
    Nella parte 3 è richiesto se si vuole stampare a schermo i risultati.

*/

using namespace std;


void macro_rlc(){ 

// PARTE 1: DATI

    // Scelta: misure in data_0 o in data_1?

    int starter = 0;
    char filename[100];

    cout << "\n\nSI VUOLE EFFETTUARE L'ANALISI DELLE MISURE NEL FILE data_0 o data_1?" << endl;
    cout << "data_0:   inserire 0 e premere INVIO" << endl;
    cout << "data_1:   inserire 1 e premere INVIO" << endl;
    cin >> starter;
    if (starter==0) sprintf(filename, "data_0.txt");
    else sprintf(filename, "data_1.txt");

    cout << "\nHai scelto di analizzare i dati nel file: " << filename << endl << endl;

    // Apertura file

    FILE *input = fopen(filename, "r" );

    if(!input)
    {
        cout << "Error: file could not be opened" << endl;
        exit(1);
    }


    // Numero di dati raccolti

    float temp_val;
    int   npoints = 0; 

    while(!feof(input))
    {
        fscanf(input,"%f\n",&temp_val);
        ++npoints;
    }

    
    npoints = npoints/5;

    cout << "Sono state raccolte: " << npoints << " triplette di valori f - V_in - V_out" << endl << endl;


    // Lettura del file

    rewind(input);

    float *frequenze = new float[npoints];
    float *V_in = new float[npoints];
    float *err_V_in = new float[npoints];
    float *V_out = new float[npoints];
    float *err_V_out = new float[npoints];


    int i=0;
    while(!feof(input))
    {
        if(i<npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            frequenze[i] = temp_val;
        }
        else if(i<2*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            V_in[i-npoints] = temp_val;
        }
        else if(i<3*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_V_in[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            V_out[i-3*npoints] = temp_val;
        }
        else if(i<5*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_V_out[i-4*npoints] = temp_val;
        }
        ++i;
    }


    


// PARTE 2: CALCOLO GUADAGNO ED ERRORI 
    
    // Errori sulle frequenze: da impostare manualmente (in base alla sensibilità dell'oscilloscoipio: 1/1000?)

    float *err_frequenze = new float[npoints];

    for(int j=0; j<npoints; j++) 
    {
        err_frequenze[j]=1/1000*frequenze[j];
    }

    // Calcolo guadagno

    float *guadagno = new float[npoints];
    float *err_guadagno = new float[npoints];

    for(int j=0; j<npoints; j++)
    {
        guadagno[j] = V_out[j] / V_in[j];
        err_guadagno[j]=sqrt(pow(err_V_out[j]/V_in[j],2)+pow(V_out[j]*err_V_in[j]/pow(V_in[j],2),2));
        //err_guadagno[j]=0.1; //In caso di prove
    }




// PARTE 3: STAMPA DEI DATI

    // Decisione: stampare o no
    int decisione_stampa;
    cout << "Desideri stampare a schermo tutti i dati?\n";
    cout << "Sì: inserire 0 e premere INVIO\n";
    cout << "No: inserire 1 e premere INVIO\n";
    cin >> decisione_stampa;

    if (decisione_stampa==0){
        cout << "\n\nTENSIONI IN INGRESSO E USCITA AL VARIARE DELLA FREQUENZA:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ") " << "f: " << frequenze[i] << "Hz     V_in: " << V_in[i] << "+-" << err_V_in[i] << "mV     V_out: " << V_out[i] << "+-" << err_V_out[i] << "mV\n";
        }

        cout << "\nGUADAGNO AL VARIARE DELLA FREQUENZA:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ") " << "f: " << frequenze[i] << "Hz     G: " << guadagno[i] << "+-" << err_guadagno[i] << endl;
        }

    }

    cout << endl << endl;




// PARTE 4: PLOT E FIT

        // Plot del guadagno G(f) 

        TCanvas *G_f = new TCanvas("RLC","Filtro passa banda",200,10,1000,700);
        G_f->SetFillColor(0);
        G_f->cd();
        TGraphErrors *gG_f = new TGraphErrors(npoints,frequenze,guadagno,err_frequenze,err_guadagno);

        // Abbellimenti 

        gG_f->SetMarkerSize(0.6);
        gG_f->SetMarkerStyle(21);
        gG_f->SetTitle("Passa Banda"); // Titolo del grafico
        gG_f->GetYaxis()->SetTitle("Guadagno"); // Titoli degli assi
        gG_f->GetXaxis()->SetTitle("Frequenza [Hz]");

        //Per impostare scala logaritmica:
        //su asse x:
        G_f->SetLogx(1);
        //su asse y:
        //G_f->SetLogy(1);

        gG_f->Draw("AP");



        // Fit G(f) 
        // G(f)= 1/(sqrt(1+(1/f^2*Df^2)(f^2-f_0^2)^2))

        TF1 *function = new TF1("Fit","1/pow(1+(1/(pow(x*[0],2)))*pow((pow(x,2)-pow([1],2)),2),0.5)",0,1000001);
        
        function->SetParameter(0,5000);
        function->SetParameter(1,11500);

        function->SetLineColor(4); // Blu
        gG_f->Fit(function,"RM+");
        gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph



        //Frequenza di risonanza osservata e larghezza di banda
        float f_ris = function->GetParameter(1);
        float err_f_ris = function->GetParError(1);
        float Df = function->GetParameter(0);
        float err_Df = function->GetParameter(1);

        cout << "\nFrequenza di Risonanza: " << f_ris << " +- " << err_f_ris << endl;
        cout << "Larghezza di Banda: " << Df << " +- " << err_Df << endl;



        // Proviamo ora ad eseguire un fit con una funzione meno generale con più parametri (da cui è stata ricavata quella precedentemente utilizzata)
        // Vuole quindi quasi essere un controllo

        // Plot del guadagno G(f) 

        TCanvas *G_f_2 = new TCanvas("RLC 2","Filtro passa banda 2",200,10,1000,700);
        G_f_2->SetFillColor(0);
        G_f_2->cd();
        TGraphErrors *gG_f_2 = new TGraphErrors(npoints,frequenze,guadagno,err_frequenze,err_guadagno);

        // Abbellimenti 

        gG_f_2->SetMarkerSize(0.6);
        gG_f_2->SetMarkerStyle(21);
        gG_f_2->SetTitle("Passa Banda"); // Titolo del grafico
        gG_f_2->GetYaxis()->SetTitle("Guadagno"); // Titoli degli assi
        gG_f_2->GetXaxis()->SetTitle("Frequenza [Hz]");

        //Per impostare scala logaritmica:
        //su asse x:
        G_f_2->SetLogx(1);
        //su asse y:
        //G_f_2->SetLogy(1);

        gG_f_2->Draw("AP");

        // Fit G(f) 
        // G = R / sqrt(R^2+(2pi f L - 1/(2pi f C))^2)         con R[0], L[1], C[2] parametri     e pi = 3.14159

        TF1 *function_2 = new TF1("Fit","[0]/pow(pow([0]+[3],2)+pow([1]*2*3.14159*x-1/([2]*2*3.14159*x),2),0.5)",0,1000001);
        
        function_2->SetParameter(0,300);
        function_2->SetParameter(1,0.006);
        function_2->SetParameter(2,30e-9);
        function_2->SetParameter(3,20);

        function_2->SetLineColor(3);
        gG_f_2->Fit(function_2,"RM+");
        gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph

        float C_2 = function_2->GetParameter(2);
        float L_2 = function_2->GetParameter(1);
        cout << "\n\nFrequenza di risonanza nuova: " << 1/(2*3.14159*sqrt(L_2*C_2)) << "\n\n";


}