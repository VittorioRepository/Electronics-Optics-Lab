/* 

INTRODUZIONE:
La macro è suddivisa in 3 parti:
    1) Lettura del file contenenti i dati
    2) Stampa a schermo degli array se necessario
    3) Plot della corrente in funzione della tensione I(V) e fit di I(V) con l'equazione di Shockley che caratterizza il diodo
       Nel caso del diodo Led: plot I(V) e V(I), fit di V(I) con l'equazione di Shockley corretta con la caduta di tensione dovuta alla resistenza interna.

    Nella parte 1 è stato implementato un sistema che permette di scegliere da terminale quale file dati far leggere al programma e che analisi eseguire.
    Nella parte 1 è richiesto anche di scegliere da terminale se si vuole già inserire gli errori o farli calcolare dal programma.
    Nella parte 3 è richiesto se si vuole stampare a schermo i risultati.
    Nella parte 4 la prima scelta provoca nel caso diodo LED una diversa analisi dati.

*/

using namespace std;


void macro_diodo(){

// PARTE 1: DATI

    // Scelta: diodo al silicio o LED?

    int starter = 0;
    char filename[100];

    cout << "\n\nSI VUOLE EFFETTUARE L'ANALISI DEL DIODO AL SILICIO O LED?" << endl;
    cout << "SILICIO:   inserire 0 e premere INVIO" << endl;
    cout << "LED:       inserire 1 e premere INVIO" << endl;
    cin >> starter;
    if (starter==0) sprintf(filename, "data_silicio.txt");
    else sprintf(filename, "data_led.txt");

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


    npoints = npoints/4;

    cout << "\nSono state raccolte: " << npoints << " coppie di valori I-V" << endl << endl;


    // Lettura del file

    rewind(input);

    float *I = new float[npoints];
    float *err_I = new float[npoints];
    float *V = new float[npoints];
    float *err_V = new float[npoints];


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
            V[i-2*npoints] = temp_val;
        }
        else if(i<4*npoints)
        {
            fscanf(input,"%f\n",&temp_val);
            err_V[i-3*npoints] = temp_val;
        }
        ++i;
    }



// PARTE 3: STAMPA DEI DATI

    // Decisione: stampare o no
    int decisione_stampa;
    cout << "Desideri stampare a schermo tutti i dati?\n";
    cout << "Sì: inserire 0 e premere INVIO\n";
    cout << "No: inserire 1 e premere INVIO\n";
    cin >> decisione_stampa;

    if (decisione_stampa==0){
        cout << "\n\nCORRENTI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << I[i] << "+-" << err_I[i] << "mA\n";
        }
        cout << "\nTENSIONI:\n";
        for(int i=0; i<npoints; i++){
            cout << i << ": " << V[i] << "+-" << err_V[i] << "mV\n";
        }
    }

    cout << endl << endl;




// PARTE 3: PLOT E FIT

    //SILICIO 

    if (starter==0)
    {

        // Plot I(V) nel caso di diodo al silicio

        TCanvas *iv_silicio = new TCanvas("Diodo I(V)","Diodo al silicio",200,10,1000,700);
        iv_silicio->SetFillColor(0);
        iv_silicio->cd();
        TGraphErrors *giv = new TGraphErrors(npoints,V,I,err_V,err_I);

        // Abbellimenti 

        giv->SetMarkerSize(0.6);
        giv->SetMarkerStyle(21);
        giv->SetTitle("I(V) Silicio"); // Titolo del grafico
        giv->GetYaxis()->SetTitle("Corrente I [mA]"); // Titoli degli assi
        giv->GetXaxis()->SetTitle("Tensione [V]");

        //Per impostare scala logaritmica:
        //su asse x:
        //iv_silicio->SetLogx(1);
        //su asse y:
        //iv_silicio->SetLogy(1);

        giv->Draw("AP");



        // Fit I(V) nel caso del diodo al silicio
        // I(V)=I_s (e^{V_d/(\eta V_T)}-1)    con I_s e \eta parametri    con V_T=k_bT/e=26 mV

        TF1 *function_1 = new TF1("Fit","[0]*(exp(x/([1]*26))-1)",0,1000);
        
        function_1->SetParameter(0,1e-11);
        function_1->SetParameter(1,1.5);

        function_1->SetLineColor(4); // Blu
        giv->Fit(function_1,"RM+");
        gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph

    }



    // LED
    if (starter==1)
    {

        // Plot I(V) nel caso di diodo LED

        TCanvas *giv_led = new TCanvas("Diodo I(V)","Diodo LED I(V)",200,10,1000,700);
        giv_led->SetFillColor(0);
        giv_led->cd();
        TGraphErrors *giv = new TGraphErrors(npoints,V,I,err_V,err_I);

        // Abbellimenti 

        giv->SetMarkerSize(0.6);
        giv->SetMarkerStyle(21);
        giv->SetTitle("I(V) Led"); // Titolo del grafico
        giv->GetYaxis()->SetTitle("Corrente I [mA]"); // Titoli degli assi
        giv->GetXaxis()->SetTitle("Tensione [V]");

        //Per impostare scala logaritmica:
        //su asse x:
        //giv_led->SetLogx(1);
        //su asse y:
        //giv_led->SetLogy(1);

        giv->Draw("AP");



        // Plot di V(I) e relativo Fit nel caso di diodo Led

        TCanvas *gvi_led = new TCanvas("Diodo V(I)","Diodo LED V(I)",200,10,1000,700);
        gvi_led->SetFillColor(0);
        gvi_led->cd();
        TGraphErrors *gvi = new TGraphErrors(npoints,I,V,err_I,err_V);

        // Abbellimenti 

        gvi->SetMarkerSize(0.6);
        gvi->SetMarkerStyle(21);
        gvi->SetTitle("V(I) Led"); // Titolo del grafico
        gvi->GetYaxis()->SetTitle("Tensione V [mV]"); // Titoli degli assi
        gvi->GetXaxis()->SetTitle("Corrente I [mA]");

        //Per impostare scala logaritmica:
        //su asse x:
        //gvi_led->SetLogx(1);
        //su asse y:
        //gvi_led->SetLogy(1);

        gvi->Draw("AP");


        // Fit V(I) nel caso del diodo LED
        // V=\eta V_T ln(I/I_s+1)+R*I    con I_s e \eta parametri    con V_T=k_bT/e=26 mV

        TF1 *function_2 = new TF1("Fit","[0]*26*log(x/[1]+1)+[2]*x",0.0001,20);

        function_2->SetParameter(0,1.5);
        function_2->SetParameter(1,1e-11);
        function_2->SetParameter(2,0);

        function_2->SetLineColor(4); // Blu
        gvi->Fit(function_2,"RM+");
        gStyle->SetOptFit(1); //print the information on fit parameters results in the statistics box directly on the TGraph


    }

    


}
