#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>//it is used for random number generation in the program
using namespace std;
class Flight {
public:
    string name;
    string departureStation;
    string destinationStation;
    string departureTime;
    string arrivalTime;
    double price;
    int availableSeats;
    string blockType;

    Flight(const string& depStation, const string& destStation, const string& className):departureStation(depStation),destinationStation(destStation),blockType(className){
        name=generateRandomName(5);
        departureTime=generateRandomTime();
        arrivalTime=generateRandomTime();
        price=rand()%1223+2777;  // Generate random price between 2777 to 3999
        availableSeats=rand()%17+31;  // Generate random seats between 31 to 47
    }
    void displayDetails()const{
        cout<<"Flight: "<<name<<"\n";
        cout<<"Departure: "<<departureStation<<"\n";
        cout<<"Destination: "<<destinationStation<<"\n";
        cout<<"Departure Time: "<<departureTime<<"\n";
        cout<<"Arrival Time: "<<arrivalTime<<"\n";
        cout<<"Price: $"<<price<<"\n";
        cout<<"Available Seats: "<<availableSeats<<"\n";
        cout<<"Block Type: "<<blockType<<"\n\n";
    }
    void displayTicket(const string& departure,const string& destination,const vector<string>& passengerNames,const vector<int>& passengerAges,const string& selectedDate) const {
        cout<<"Ticket Details:\n";
        cout<<"Flight: "<<name<<"\n";
        cout<<"Departure: "<<departureStation<<"\n";
        cout<<"Destination: "<<destinationStation<<"\n";
        cout<<"Departure Time: "<<departureTime<<"\n";
        cout<<"Arrival Time: "<<arrivalTime<<"\n";
        cout<<"Price: $"<<price<<"\n";

        cout<<"Date of Travel: "<<selectedDate<<"\n";
        cout<<"\nPassenger Details:\n";
        for (size_t i=0;i<passengerNames.size();++i) {
            cout<<"Passenger " <<i + 1 << ": " <<passengerNames[i]<<" (Age: "<<passengerAges[i]<<")\n";
        }
        cout<<"\nTotal Price: $" << price * passengerNames.size() << "\n";
        cout<<"Block Type: "<<blockType<<"\n";
    }
private:
    static string generateRandomName(int length){//length of 5 letters
        const string alphabet="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        string randomName;
        for (int i=0;i<length;++i) {
            randomName+=alphabet[rand()%alphabet.length()];
        }
        return randomName;
    }
    static string generateRandomTime(){
        int hours=rand()%24;
        int minutes=rand()%60;
        return (hours<10?"0":"")+to_string(hours)+":"+(minutes<10?"0":"")+to_string(minutes);
    }
};
void displayDatesInColumns(const vector<string>& dates,int numColumns) {
    for (size_t i=0;i<dates.size();++i) {
        cout <<i+1<< ". "<<dates[i]<<"\t";
        if ((i + 1)%numColumns==0||i==dates.size()-1){
            cout<<"\n";
        }
    }
}
void displayFlightDetails(const vector<Flight>& flights, const string& selectedDate) {
    cout<< "Available Flights for "<<selectedDate<<":\n";
    for (size_t i=0;i<flights.size();++i) {
        cout<<"Index "<<i+1<<":\n";
        flights[i].displayDetails();
    }
}
class BusTicket{
private:
    string from;
    string to;
    int numDates;
    string busType;
    int numPassengers;
    int selectedDateIndex;
    string pnr;
    double totalFare;
    string convertToWords(int num){
        const string units[]={"", "One","Two","Three","Four","Five","Six","Seven","Eight","Nine"};
        const string teens[]={"","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"};
        const string tens[]={"", "","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};   
     string words="";

    if (num>=1000){
        words+=convertToWords(num/1000)+" Thousand";
        num%=1000;
    }

    if (num>=100) {
        words+=convertToWords(num/100)+" Hundred ";
        num%=100;
    }

    if (num>=20) {
        words+=tens[num/10]+" ";
        num%=10;
    } else if(num>=11) {
        words+=teens[num-10]+" ";
        num=0;
    }
    words+=units[num];

    return words;
}
        
    string convertPaiseToWords(int paise) {
        if (paise==0) {
            return "";
        }
        return " and "+convertToWords(paise)+" Paise";
    }

public:
    BusTicket(){
        srand(static_cast<unsigned>(time(0)));
        selectedDateIndex=-1;
    }

    void askCityDetails(){
        cout<<"Enter the starting city: ";
        getline(cin,from);
        cout<<"Enter the destination city: ";
        getline(cin,to);
    }

    void displayAvailableDates(){
        // Get the current date
        time_t now=time(nullptr);
        struct tm *current_date=localtime(&now);
        int num_dates=30;
        int dates_per_column=5;
       cout << "Available Dates to Select:\n";
        for (int i=1;i<=num_dates;i++){
            time_t future_date=now+i*24*60*60; 
            struct tm *date_info=localtime(&future_date);
            cout<<i<<". Date "<<(date_info->tm_mday)<<"/"<< (date_info->tm_mon + 1)<<"/"<<(date_info->tm_year+1900)<<"\t";
            if (i % dates_per_column==0){
                cout <<endl;
            }
        }
        cout<<"\nEnter the position of the date to select (1-"<<num_dates<<"): ";
        cin>>selectedDateIndex;
    }
    void bookTicket(){
        cout<<"Select bus type:\n";
       cout<<"1. Luxury Seating Bus\n";
        cout<<"2. Luxury Sleeper Bus\n";
        cin>>busType;

        if (busType!="1"&&busType!="2") {
            cout<<"Invalid choice. Exiting...\n";
            return;
        }
        buuu:
        cout<<"Enter the number of passengers: ";
        cin>>numPassengers;
        cin.ignore();
       if(numPassengers>6){
        cout<<"At one time you can book only 6 seats! select number of seats again!!\n";
        goto buuu;
    }
        pnr=generatePNR();
        totalFare=0;
        cout<<"Enter passenger details:\n";
        for (int i=0; i<numPassengers;i++) {
            string name;
            int age;
            int seatNumber=generateSeatNumber();
            cout<<"Passenger "<<i+1<<" Name: ";
            getline(cin,name);
            cout<<"Passenger "<<i+1<<" Age: ";
            cin>>age;
            cin.ignore();
            int ticketFare=generateTicketFare(busType=="2");
            totalFare+=ticketFare;
        }
    }
    string generatePNR(){
       string pnr = "";
        for (int i=0;i<10;i++) {
            pnr+=to_string(rand()%9+1);
        }
        return pnr;
    }
    int generateSeatNumber() {
        return rand()%45+1;
    }
    int generateTicketFare(bool isSleeper){
        if (isSleeper) {
            return 2511+(rand()%489); //random fare between 2511 to 2999
        } else {
            return 1511+(rand()%489); // Random fare between 1511 to 1999
        }
    } 
    string convertToWords(double amount){
        if (amount==0){
            return "Zero";
        }
        int rupees=static_cast<int>(amount);
        int paise=static_cast<int>((amount-rupees)*100);
        string result=convertToWords(rupees)+" Rupees"+convertPaiseToWords(paise);
        return result+" only";
    }

    void displayTicketDetails(){
        cout<<"Ticket Details:\n";
        cout<<"From: "<<from<<", To: "<<to<< "\n";
        if (selectedDateIndex>=0){
            // Get the current date
            time_t now=time(nullptr);
            struct tm *current_date=localtime(&now);
            time_t boarding_date=now+selectedDateIndex*24*60*60;
            struct tm *boarding_date_info=localtime(&boarding_date);
            cout<<"Boarding Date on: "<<(boarding_date_info->tm_mday)<<"/"<<(boarding_date_info->tm_mon+1)<<"/" <<(boarding_date_info->tm_year+1900)<<"\n";
        }
       cout<<"PNR No: "<<pnr<<"\n";
       cout<<"Ticket Fare: "<<totalFare<<"\n";
       cout<<"Convenience Fare: "<<0.05*totalFare<<"\n";
       cout<<"Total Fare: " <<totalFare * 1.05<<"\n";
       cout<<"Total Fare in Words: "<<convertToWords(totalFare*1.05)<<"\n";
    }
    ~BusTicket() {
    }
};
const int numBlocks=12;
const int seatsPerBlock=62;
const int numNonACBlocks=7;
const int numACBlocks=3;
 string numberToWords(int num) {
        const string units[]={"", "One","Two","Three","Four","Five","Six","Seven","Eight","Nine"};
        const string teens[]={"","Eleven","Twelve","Thirteen","Fourteen","Fifteen","Sixteen","Seventeen","Eighteen","Nineteen"};
        const string tens[]={"", "","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety"};
        
     string words="";
    if (num>=1000){
        words+=numberToWords(num/1000)+" Thousand";
        num%=1000;
    }
    if (num >= 100) {
        words+=numberToWords(num/100)+" Hundred ";
        num%=100;
    }
    if (num>=20) {
        words+=tens[num/10]+" ";
        num%=10;
    } else if(num>=11) {
        words+=teens[num-10]+" ";
        num=0;
    }
    words+=units[num];
    return words;
}

class Passenger{
public:
    string name;
    int age;
    string seat;
    // Constructor to initialize passenger details
    Passenger(string passengerName,int passengerAge,string passengerSeat) {
        name=passengerName;
        age=passengerAge;
        seat=passengerSeat;
    }
};
tm getTomorrowDate();
class TrainTicket{
public:
    string source;
    string destination;
    vector<Passenger>passengers;
    int selectedDateIndex; 

    TrainTicket(string src,string dest){
        source=src;
        destination=dest;
        selectedDateIndex=-1; 
    }
    void addPassenger(string name,int age,string seat) {  
        passengers.push_back(Passenger(name,age,seat));
    }
    void displayTicketInfo() {
        cout<<"Source: "<<source<<endl;
        cout<<"Destination: "<<destination<<endl;

        if (selectedDateIndex>=0){
            tm tomorrow=getTomorrowDate();
            tomorrow.tm_mday+=selectedDateIndex;
            mktime(&tomorrow);
            cout<<"Selected Date: "<<tomorrow.tm_mday<<"/"<<tomorrow.tm_mon+1<<"/"<<tomorrow.tm_year+1900<<endl;
        }

        cout<<"PNR Number: "<<generatePNR()<<endl;
        cout<<"Passengers:\n";
        for (size_t i=0;i<passengers.size();++i){
            const Passenger& passenger=passengers[i];
            cout<<"Name: "<<passenger.name << ", Age: "<<passenger.age<<", Seat: "<<passenger.seat<<endl;
        }

        double charges=calculateCharges();
        cout<<"Total fare: "<<charges<<endl;

        cout<<"Total fare in words: "<<numberToWords(static_cast<int>(charges))<<endl;
    }
    string generatePNR(){
        srand(time(0));
        string pnr="";
        for (int i=0;i<10;i++) {
            int digit=rand()%10;
            pnr+=to_string(digit);
        }
        return pnr;
    }
    double calculateCharges(){
        double charges = 0.0;
        for (size_t i=0; i<passengers.size();++i) {
            const Passenger& passenger=passengers[i];
            int chargeRangeMin,chargeRangeMax;
            if (passenger.seat.find("AC SLEEPER")!=string::npos) {
                chargeRangeMin=1027;
                chargeRangeMax=1499;
            } else if (passenger.seat.find("SLEEPER")!=string::npos) {
                chargeRangeMin = 531;
                chargeRangeMax = 799;
            } else if (passenger.seat.find("GENERAL")!=string::npos) {
                chargeRangeMin=201;
                chargeRangeMax=499;
            }
            int charge=rand()%(chargeRangeMax-chargeRangeMin+1)+chargeRangeMin;
            charges+=charge;
        }

        if (!passengers.empty()&&passengers[0].seat.find("AC SLEEPER")!=string::npos) {
            double gst=0.05*charges;
            charges+=gst;
        }

        return charges;
    }
};
tm getTomorrowDate(){
    time_t t=time(0);
    tm* tomorrow=localtime(&t);
    tomorrow->tm_mday+=1;
    mktime(tomorrow);
    return *tomorrow;
}
void displayAvailableDates(){
    tm tomorrow = getTomorrowDate();
    cout << "Available Dates:\n";
    for (int i=0;i<30;++i){
        cout<<i<< ". "<<tomorrow.tm_mday<<"/"<<tomorrow.tm_mon+1<<"/"<<tomorrow.tm_year+1900<<"\t";
        if ((i+1)%5==0) {
            cout<<endl;
        }
        tomorrow.tm_mday+=1;
        mktime(&tomorrow);
    }
    cout<<endl;
}
string randomSeat(int blockIndex,const string& blockType){
    srand(time(0));
    int seatNumber=rand()%seatsPerBlock+1;
    return blockType+"-BLOCK "+to_string(blockIndex+1)+":"+to_string(seatNumber);
}

int main(){
    int ch;
    cout<<"                                          WELCOME!!              \n\n";
 	cout<<"\t\t\t*********************************************\n";
	cout<<"\t\t\t*                                           *\n";
	cout<<"\t\t\t*       ----------------------------        *\n";
	cout<<"\t\t\t*       #      booking sphere      #        *\n";
	cout<<"\t\t\t*       ----------------------------        *\n";
	cout<<"\t\t\t*                                           *\n";
	cout<<"\t\t\t*                                           *\n";
	cout<<"\t\t\t*                                           *\n";
	cout<<"\t\t\t*********************************************\n\n";
    do{
    cout<<"\n\t\tenter which transport you want to choice for your journey!!!";
    cout<<"\n1.flight\n2.train\n3.bus:";
    cin>>ch;
    cin.ignore();
    switch(ch){
        case 1:{
    srand(static_cast<unsigned>(time(0)));
    string departure,destination;
    cout<<"Enter Departure Station: ";
   getline(cin,departure);
    cout<<"Enter Destination Station: ";
    getline(cin,destination);
    vector<string>dates;
    time_t t=time(0);
    tm* now=localtime(&t);
    now->tm_mday+=1;
    mktime(now);

    for (int i=0;i<30;++i){
        string date=to_string(now->tm_year+1900)+"-"+(now->tm_mon+1<10?"0":"")+to_string(now->tm_mon+1)+"-"+(now->tm_mday<10?"0":"")+to_string(now->tm_mday);
        dates.push_back(date);
        now->tm_mday+=1;
        mktime(now);
    }
    cout<<"Available Dates:\n";
    displayDatesInColumns(dates,5);
    int selectedDateIndex;
    do{
        cout<<"Select the index of the date: ";
        cin>>selectedDateIndex;
        if(selectedDateIndex<1||selectedDateIndex>static_cast<int>(dates.size())){
            cout << "Invalid index. Please select again!\n";
        }
    }while(selectedDateIndex<1||selectedDateIndex>static_cast<int>(dates.size()));

    int selectedClass;
    do{
        cout<<"\nChoose Class:\n";
        cout<<"1. Economy Class\n";
        cout<<"2. Premium Economy Class\n";
        cout<<"3. Business Class\n";
        cout<<"Select the index of the class: ";
        cin>>selectedClass;

        if(selectedClass<1||selectedClass>3){
            cout<<"Invalid index. Please select again!\n";
        }
    }while(selectedClass<1||selectedClass>3);

    vector<Flight>flights;
    switch(selectedClass){
        case 1:
            for(int i=0;i<3;++i){
            flights.emplace_back(departure, destination,"Economy Class");
            }
            break;
        case 2:
            for(int i=0;i<3;++i){
                flights.emplace_back(departure,destination,"Premium Economy Class");
            }
            break;
        case 3:
            for(int i=0;i<3;++i){
                flights.emplace_back(departure, destination,"Business Class");
            }
            break;
    }
    displayFlightDetails(flights,dates[selectedDateIndex-1]);
    int selectedFlightIndex;
    do{
        cout<<"Select the index of the flight: ";
        cin>>selectedFlightIndex;
        if(selectedFlightIndex<1||selectedFlightIndex>static_cast<int>(flights.size())){
            cout<<"Invalid index. Please select again!\n";
        }
    }while(selectedFlightIndex<1||selectedFlightIndex>static_cast<int>(flights.size()));
    int numPassengers;
    ctt:
    cout<<"Enter the number of passengers: ";
    cin>>numPassengers;
    cin.ignore();
    if(numPassengers>6){
        cout<<"At one time you can book only 6 seats! select number of seats again!!";
        goto ctt;
    }
    vector<string>passengerNames;
    vector<int>passengerAges;
    for (int i=0;i<numPassengers;++i) {
        string name;
        int age;
        cout<<"Enter passenger "<<i+1<<" name: ";
        getline(cin,name);
        cout<<"Enter passenger "<<i+1<<" age: ";
        cin>>age;
        cin.ignore();
        passengerNames.push_back(name);
        passengerAges.push_back(age);
    }
    flights[selectedFlightIndex-1].displayTicket(departure,destination,passengerNames,passengerAges,dates[selectedDateIndex-1]);
    exit(0);
    }
    case 2: {
    string source,destination;
    int numPassengers;

    cout<<"Enter the departure station: ";
    getline(cin,source);

    cout<<"Enter the destination station: ";
    getline(cin,destination);

    displayAvailableDates();

    cout<<"Enter the selected date index from 1-30: ";
    TrainTicket ticket(source,destination);
    cin>>ticket.selectedDateIndex;

    // Validate the selected date index
    if (ticket.selectedDateIndex < 1 || ticket.selectedDateIndex > 30) {
        cout<<"Invalid date index. Exiting...\n";
        return 1;
    }

    cout<<"Select the block type for travelling:\n";
    cout<<"1. AC\n";
    cout<<"2. Non-AC\n";
    cout<<"3. General\n";
    int blockChoice;
    cin>>blockChoice;
    cin.ignore();

    string blockType;

    switch (blockChoice) {
        case 1:
            blockType="AC SLEEPER";
            break;
        case 2:
            blockType="SLEEPER";
            break;
        case 3:
            blockType="GENERAL";
            break;
        default:
            cout<<"Invalid block type selection. Exiting...\n";
            return 1;
    }
    xx:
    cout<<"Enter the number of passengers: ";
    cin>>numPassengers;
    cin.ignore();
    if(numPassengers>6){
        cout<<"At one time you can book only 6 seats. Book AGAIN!!";
        goto xx;
    }
    for (int i=0;i<numPassengers;i++) {
        string name;
        int age;
        cout<<"Enter the name of Passenger "<<i+1<<": ";
        getline(cin,name);
        cout<<"Enter the age of Passenger "<<i+1<<": ";
        cin>>age;
        cin.ignore(); 
        string seat=randomSeat(0,blockType); 
        ticket.addPassenger(name,age,seat);
    }

    
    cout<<"\nTicket Details:\n";
    ticket.displayTicketInfo();

    exit(0);
    }
    case 3:{
    BusTicket aticket;
    aticket.askCityDetails();
    aticket.displayAvailableDates();
    aticket.bookTicket();
    cout<<"\n";
    aticket.displayTicketDetails();
    std::cout << "Happy Journey! Visit again!\n";
     exit(0);
    }
    
     default:cout<<"try again!!\n";
   
    }
}while(ch!=3);
return 0;
}


