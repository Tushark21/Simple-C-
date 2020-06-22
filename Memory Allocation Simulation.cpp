#include<bits/stdc++.h>

using namespace std;
using namespace std::chrono;

struct Node
{   
    bool isAllocated;
    long long int base,limit;
    Node *prev,*next;
}*head,*prevHole;

long long int memorySize,noOfProcesses;
vector<int> originalBurstTime(noOfProcesses);
    
vector<int> fFBurstTime(noOfProcesses);
vector<int> mWFBurstTime(noOfProcesses);
vector<int> wFBurstTime(noOfProcesses);

vector<int> arrivalTime(noOfProcesses);
vector<int> processSize(noOfProcesses);

vector<Node *> firstFitLoc(noOfProcesses);
vector<Node *> modifiedWorstFitLoc(noOfProcesses);
vector<Node *> worstFitLoc(noOfProcesses);

//---------------Parameters to be Recorded-----------------
vector<long long int> fFAllocationTime(noOfProcesses);
vector<long long int> fFDeAllocationTime(noOfProcesses);
vector<long long int> fFAllocatedAtTurn(noOfProcesses);

vector<long long int> mWFAllocationTime(noOfProcesses);
vector<long long int> mWFDeAllocationTime(noOfProcesses);
vector<long long int> mWFAllocatedAtTurn(noOfProcesses);

vector<long long int> wFAllocationTime(noOfProcesses);
vector<long long int> wFDeAllocationTime(noOfProcesses);
vector<long long int> wFAllocatedAtTurn(noOfProcesses);

long long int fFTotalAlloctionTime=0,fFTotalDeAllocationTime=0;
long long int wFTotalAlloctionTime=0,wFTotalDeAllocationTime=0;
long long int mWFTotalAlloctionTime=0,mWFTotalDeAllocationTime=0;

//clock_t tempStart,tempEnd;

int timeQuantum=4;
int deAllocTicks=0;
int allocTicks=0;

void traverseList(){
    Node* ptr=new Node;
    ptr=head;
    while(ptr!=NULL){
        cout<<"Free:"<<!ptr->isAllocated<<" Base:"<<ptr->base<<" Limit:"<<ptr->limit<<"-->\n";
        ptr=ptr->next;
    }
    cout<<"\n";
}

void reverseTraverseList(){
    cout<<"Reverse:\n";
    Node* ptr=new Node;
    ptr=head;
    while(ptr!=NULL){
        if(ptr->next==NULL){
            break;
        }
        ptr=ptr->next;
    }

    while(ptr!=NULL){
        cout<<"Free:"<<!ptr->isAllocated<<" Base:"<<ptr->base<<" Limit:"<<ptr->limit<<"-->\n";
        ptr=ptr->prev;
    }
    cout<<"\n";
}

Node* allocate(Node *curr,long long int size){

    Node *ptr=new Node;
    if(ptr==NULL){
        cout<<"Can't Allocate Memory\n";
    }

    if(curr->next==NULL){
        allocTicks++;
        ptr->base=curr->base+curr->limit-size+1;
        ptr->limit=size;
        ptr->isAllocated=true;

        curr->limit=curr->limit-size;

        ptr->prev=curr;
        ptr->next=curr->next;
        curr->next=ptr;

        //cout<<"in\n";
        return ptr;
    }

    allocTicks++;
    ptr->base=curr->base+curr->limit-size+1;
    ptr->limit=size;
    ptr->isAllocated=true;

    curr->limit=curr->limit-size;

    ptr->prev=curr;
    ptr->next=curr->next;
    curr->next->prev=ptr;
    curr->next=ptr;

    //cout<<"out\n";
    return ptr;
}

void deAllocate(Node* node){

    node->isAllocated=false;
    Node* save=new Node;
    deAllocTicks++;

    if(save==NULL){
        cout<<"Can't Allocate Memory for save\n";
    }

    save=node;
    if(node->prev!=NULL && !(node->prev->isAllocated)){
        deAllocTicks++;
        node->prev->limit+=node->limit;

        node->prev->next=node->next;
        if(node->next!=NULL){
            node->next->prev=node->prev;
        }
        node=node->prev;

        save->prev=NULL;
        save->next=NULL;
        
        delete(save);
    }

    if(node->next!=NULL && !(node->next->isAllocated)){
        deAllocTicks++;
        save=node->next;
        node->limit+=node->next->limit;

        if(node->next->next!=NULL){
            node->next->next->prev=node;
        }

        node->next=node->next->next;

        save->prev=NULL;
        save->next=NULL;
        
        delete(save);
    }
}

Node* firstFit(long long int processId,long long int size){
    Node* ptr=new Node;
    if(ptr==NULL){
        cout<<"Can't Allocate Memory in First Fit\n";
    }
    ptr=head;
    //cout<<size<<" "<<ptr->limit<<" "<<ptr->isAlfirstFitLocated;
    while(ptr!=NULL){
        fFAllocationTime[processId]++;
        if(ptr->limit>=size && !(ptr->isAllocated)){
            //cout<<"Hole Found, Base:"<<ptr->base<<" Limit: "<<ptr->limit<<"\n";
            return(allocate(ptr,size));
        }
        ptr=ptr->next;
    }

    //cout<<"NULL\n";
    return NULL;
}


Node* modifiedWorstFit(long long int processId,long long int size){
    if(prevHole!=NULL && prevHole->limit>=size && !(prevHole->isAllocated)){
        mWFAllocationTime[processId]++;
        //cout<<processId<<",";
        return (allocate(prevHole,size));
    }

    mWFAllocationTime[processId]++;
    Node* ptr=new Node;
    if(ptr==NULL){
        cout<<"Can't Allocate Memory in Modified Worst Fit\n";
    }

    ptr=head;
    prevHole=head;
    
    while(ptr!=NULL){
        mWFAllocationTime[processId]++;
        if(prevHole->limit<ptr->limit && !(ptr->isAllocated)){
            prevHole=ptr;
        }
        ptr=ptr->next;
    }
    if(prevHole->limit>=size && !(prevHole->isAllocated)){
        return (allocate(prevHole,size));
    }

    return NULL;
}

Node* worstFit(long long int processId,long long int size){
    Node* ptr=new Node;
    if(ptr==NULL){
        cout<<"Can't Allocate Memory in Worst Fit\n";
    }

    ptr=head;
    prevHole=head;

    while(ptr!=NULL){
        wFAllocationTime[processId]++;
        if(prevHole->limit<ptr->limit && !(ptr->isAllocated)){
            prevHole=ptr;
        }
        ptr=ptr->next;
    }

    if(prevHole->limit>=size && !(prevHole->isAllocated)){
        return (allocate(prevHole,size));
    }

    return NULL;
}

//-----------------------------First Fit Execution----------------------
void executeFirstFit(){
    /*
    for(long long int i=0;i<noOfProcesses;i++){
        cout<<arrivalTime[i]<<":";
        cout<<fFBurstTime[i]<<":";
        cout<<processSize[i]<<" Bytes\n";
    }
    cout<<"\n";
    */

    for(long long int i=0;i<noOfProcesses;i++){
        fFAllocationTime[i]=0;
        fFDeAllocationTime[i]=0;
        fFAllocatedAtTurn[i]=0;

        fFBurstTime[i]=originalBurstTime[i];
        firstFitLoc[i]=NULL;
    }

    fFTotalAlloctionTime=0;
    fFTotalDeAllocationTime=0;

    queue<long long int> readyQueue;

    long long int processId,burstTimeTemp=0,currTime=0,arrivedProcesses=0,completedProcesses=0;
    bool isExecuting=false,needToPush=false;
    int time=0;

    int loadIndex=0;
    cout<<"Simulating First Fit:\n\n";
    while(!readyQueue.empty() || completedProcesses!=noOfProcesses){
        switch(loadIndex%1000){
            case 0:
                cout<<"\b";
                cout<<"|";
                break;
            case 300:
                cout<<"\b";
                cout<<"/";
                break;
            case 600:
                cout<<"\b";
                cout<<"-";
                break;

            case 900:
                cout<<"\b";
                cout<<"\\";
                break;
            default:
                cout<<"";
        }

        loadIndex++;

        if(!readyQueue.empty() && !isExecuting){
            processId=readyQueue.front();
            readyQueue.pop();

            if(fFBurstTime[processId]>timeQuantum){
                needToPush=true;
                burstTimeTemp=timeQuantum;
                fFBurstTime[processId]-=timeQuantum;
            }
            else{
                burstTimeTemp=fFBurstTime[processId];
            }
            isExecuting=true;
            time=1;
            //cout<<"Process with Process Id:"<<processId<<" Executing...\n";
        }

        for(;arrivedProcesses<noOfProcesses;arrivedProcesses++){
            if(arrivalTime[arrivedProcesses]<=currTime){
                //tempStart=clock();
                firstFitLoc[arrivedProcesses]=firstFit(arrivedProcesses,processSize[arrivedProcesses]);
                //tempEnd=clock();
                //fFAllocationTime[arrivedProcesses]=double(tempEnd-tempStart)/double(CLOCKS_PER_SEC);
                fFAllocationTime[arrivedProcesses]+=allocTicks;
                allocTicks=0;
                fFTotalAlloctionTime+=fFAllocationTime[arrivedProcesses];

                if(firstFitLoc[arrivedProcesses]==NULL){
                    //cout<<"No Available Hole\n";
                    fFAllocatedAtTurn[arrivedProcesses]+=1;
                    break;
                }
                else{
                    //cout<<"Allocated Block:\nFree:"<<firstFitLoc[arrivedProcesses]->isAllocated<<" Base:"<<firstFitLoc[arrivedProcesses]->base<<" limit:"<<firstFitLoc[arrivedProcesses]->limit<<"\n\n";
                    readyQueue.push(arrivedProcesses);
                    fFAllocatedAtTurn[arrivedProcesses]+=1;
                    //cout<<"Memory Allocated\n";
                    //traverseList();
                }
            }
            else{
                break;
            }
        }

        if(isExecuting && time==burstTimeTemp){
            if(needToPush){
                readyQueue.push(processId);
                //cout<<"Process with Process Id:"<<processId<<" Pushed Back at "<<currTime<<".\n\n";
            }
            else{
                //cout<<"Process with Process Id:"<<processId<<" Finished at "<<currTime<<".\n\n";
                
                deAllocate(firstFitLoc[processId]);
                fFDeAllocationTime[processId]+=deAllocTicks;
                deAllocTicks=0;
                //fFDeAllocationTime[processId]=double(tempEnd-tempStart)/double(CLOCKS_PER_SEC);
                fFTotalDeAllocationTime+=fFDeAllocationTime[processId];
                //traverseList();
                //reverseTraverseList();
                completedProcesses++;
            }
            isExecuting=false;
            needToPush=false;
        }

        time++;
        currTime++;
    }
    cout<<"\b";
}

//-------------------------Worst Fit Execution-------------------------
void executeWorstFit(){
    /*
    for(long long int i=0;i<noOfProcesses;i++){
        cout<<arrivalTime[i]<<":";
        cout<<fFBurstTime[i]<<":";
        cout<<processSize[i]<<" Bytes\n";
    }
    cout<<"\n";
    */

    for(long long int i=0;i<noOfProcesses;i++){
        wFAllocationTime[i]=0;
        wFDeAllocationTime[i]=0;
        wFAllocatedAtTurn[i]=0;

        wFBurstTime[i]=originalBurstTime[i];
        worstFitLoc[i]=NULL;
    }

    wFTotalAlloctionTime=0;
    wFTotalDeAllocationTime=0;

    queue<long long int> readyQueue;

    long long int processId,burstTimeTemp=0,currTime=0,arrivedProcesses=0,completedProcesses=0;
    bool isExecuting=false,needToPush=false;
    int time=0;
    
    int loadIndex=0;
    cout<<"Simulating Worst Fit\n\n";

    while(!readyQueue.empty() || completedProcesses!=noOfProcesses){

        switch(loadIndex%1000){
            case 0:
                cout<<"\b";
                cout<<"|";
                break;
            case 300:
                cout<<"\b";
                cout<<"/";
                break;
            case 600:
                cout<<"\b";
                cout<<"-";
                break;

            case 900:
                cout<<"\b";
                cout<<"\\";
                break;
            default:
                cout<<"";
        }

        loadIndex++;

        if(!readyQueue.empty() && !isExecuting){
            processId=readyQueue.front();
            readyQueue.pop();

            if(wFBurstTime[processId]>timeQuantum){
                needToPush=true;
                burstTimeTemp=timeQuantum;
                wFBurstTime[processId]-=timeQuantum;
            }
            else{
                burstTimeTemp=wFBurstTime[processId];
            }
            isExecuting=true;
            time=1;
            //cout<<"Process with Process Id:"<<processId<<" Executing...\n";
        }

        for(;arrivedProcesses<noOfProcesses;arrivedProcesses++){
            if(arrivalTime[arrivedProcesses]<=currTime){
                worstFitLoc[arrivedProcesses]=worstFit(arrivedProcesses,processSize[arrivedProcesses]);
                //wFAllocationTime[arrivedProcesses]=double(tempEnd-tempStart)/double(CLOCKS_PER_SEC);
                wFAllocationTime[arrivedProcesses]+=allocTicks;
                allocTicks=0;
                wFTotalAlloctionTime+=wFAllocationTime[arrivedProcesses];
                
                if(worstFitLoc[arrivedProcesses]==NULL){
                    //cout<<"No Available Hole\n";
                    wFAllocatedAtTurn[arrivedProcesses]+=1;
                    break;
                }
                else{
                    //cout<<"Allocated Block:\nFree:"<<worstFitLoc[arrivedProcesses]->isAllocated<<" Base:"<<worstFitLoc[arrivedProcesses]->base<<" limit:"<<worstFitLoc[arrivedProcesses]->limit<<"\n\n";
                    readyQueue.push(arrivedProcesses);
                    wFAllocatedAtTurn[arrivedProcesses]+=1;
                    //cout<<"Memory Allocated\n";
                    //traverseList();
                }
            }
            else{
                break;
            }
        }

        if(isExecuting && time==burstTimeTemp){
            if(needToPush){
                readyQueue.push(processId);
                //cout<<"Process with Process Id:"<<processId<<" Pushed Back at "<<currTime<<".\n\n";
            }
            else{
                //cout<<"Process with Process Id:"<<processId<<" Finished at "<<currTime<<".\n\n";
                deAllocate(worstFitLoc[processId]);
                wFDeAllocationTime[processId]+=deAllocTicks;
                deAllocTicks=0;
                //wFDeAllocationTime[processId]=double(tempEnd-tempStart)/double(CLOCKS_PER_SEC);
                wFTotalDeAllocationTime+=wFDeAllocationTime[processId];
                //traverseList();
                //reverseTraverseList();
                completedProcesses++;
            }
            isExecuting=false;
            needToPush=false;
        }

        time++;
        currTime++;
    }
    cout<<"\b";
}

//---------------------Modified Worst Fit Execution---------------------
void executeModifiedWorstFit(){
    /*
    for(long long int i=0;i<noOfProcesses;i++){
        cout<<arrivalTime[i]<<":";
        cout<<fFBurstTime[i]<<":";
        cout<<processSize[i]<<" Bytes\n";
    }
    cout<<"\n";
    */

    for(long long int i=0;i<noOfProcesses;i++){
        mWFAllocationTime[i]=0;
        mWFDeAllocationTime[i]=0;
        mWFAllocatedAtTurn[i]=0;

        mWFBurstTime[i]=originalBurstTime[i];
        modifiedWorstFitLoc[i]=NULL;
    }

    prevHole=head;
    mWFTotalAlloctionTime=0;
    mWFTotalDeAllocationTime=0;

    queue<long long int> readyQueue;

    long long int processId,burstTimeTemp=0,currTime=0,arrivedProcesses=0,completedProcesses=0;
    bool isExecuting=false,needToPush=false;
    int time=0;
    
    int loadIndex=0;
    cout<<"Simulating Modified Worst Fit\n\n";

    while(!readyQueue.empty() || completedProcesses!=noOfProcesses){
        switch(loadIndex%1000){
            case 0:
                cout<<"\b";
                cout<<"|";
                break;
            case 300:
                cout<<"\b";
                cout<<"/";
                break;
            case 600:
                cout<<"\b";
                cout<<"-";
                break;

            case 900:
                cout<<"\b";
                cout<<"\\";
                break;
            default:
                cout<<"";
        }

        loadIndex++;

        if(!readyQueue.empty() && !isExecuting){
            processId=readyQueue.front();
            readyQueue.pop();

            if(mWFBurstTime[processId]>timeQuantum){
                needToPush=true;
                burstTimeTemp=timeQuantum;
                mWFBurstTime[processId]-=timeQuantum;
            }
            else{
                burstTimeTemp=mWFBurstTime[processId];
            }
            isExecuting=true;
            time=1;
            //cout<<"Process with Process Id:"<<processId<<" Executing...\n";
        }

        for(;arrivedProcesses<noOfProcesses;arrivedProcesses++){
            if(arrivalTime[arrivedProcesses]<=currTime){
                modifiedWorstFitLoc[arrivedProcesses]=modifiedWorstFit(arrivedProcesses,processSize[arrivedProcesses]);
                //mWFAllocationTime[arrivedProcesses]=(double(tempEnd-tempStart)/double(CLOCKS_PER_SEC));
                mWFAllocationTime[arrivedProcesses]+=allocTicks;
                allocTicks=0;
                mWFTotalAlloctionTime+=mWFAllocationTime[arrivedProcesses];

                if(modifiedWorstFitLoc[arrivedProcesses]==NULL){
                    //cout<<"No Available Hole\n";
                    mWFAllocatedAtTurn[arrivedProcesses]+=1;
                    break;
                }
                else{
                    //cout<<"Allocated Block:\nFree:"<<modifiedWorstFitLoc[arrivedProcesses]->isAllocated<<" Base:"<<modifiedWorstFitLoc[arrivedProcesses]->base<<" limit:"<<modifiedWorstFitLoc[arrivedProcesses]->limit<<"\n\n";
                    readyQueue.push(arrivedProcesses);
                    mWFAllocatedAtTurn[arrivedProcesses]+=1;
                    //cout<<"Memory Allocated\n";
                    //traverseList();
                }
            }
            else{
                break;
            }
        }

        if(isExecuting && time==burstTimeTemp){
            if(needToPush){
                readyQueue.push(processId);
                //cout<<"Process with Process Id:"<<processId<<" Pushed Back at "<<currTime<<".\n\n";
            }
            else{
                //cout<<"Process with Process Id:"<<processId<<" Finished at "<<currTime<<".\n\n";
                deAllocate(modifiedWorstFitLoc[processId]);
                mWFDeAllocationTime[processId]+=deAllocTicks;
                deAllocTicks=0;
                //mWFDeAllocationTime[processId]=(double(tempEnd-tempStart)/double(CLOCKS_PER_SEC));
                mWFTotalDeAllocationTime+=mWFDeAllocationTime[processId];
                //traverseList();
                //reverseTraverseList();
                completedProcesses++;
            }
            isExecuting=false;
            needToPush=false;
        }

        time++;
        currTime++;
    }
    cout<<"\b";
}

//------------------Main-------------------
int main()
{
    string fileName;
    cout<<"Enter File Name\n";
    cin>>fileName;

    cout<<"Enter No. Of Processes:\n";
    cin>>noOfProcesses;
    cout<<"Enter Memory Size:\n";
    cin>>memorySize;

    prevHole=new Node;
    head=new Node;
    head->prev=NULL;
    head->next=NULL;
    head->isAllocated=false;
    head->base=0;
    head->limit=memorySize;

    traverseList();

    srand(time(0));

    originalBurstTime.resize(noOfProcesses);
    
    fFBurstTime.resize(noOfProcesses);
    mWFBurstTime.resize(noOfProcesses);
    wFBurstTime.resize(noOfProcesses);
    
    arrivalTime.resize(noOfProcesses);
    processSize.resize(noOfProcesses);

    firstFitLoc.resize(noOfProcesses);
    modifiedWorstFitLoc.resize(noOfProcesses);
    worstFitLoc.resize(noOfProcesses);

    //---------------Parameters to be Recorded-----------------
    fFAllocationTime.resize(noOfProcesses);
    fFDeAllocationTime.resize(noOfProcesses);
    fFAllocatedAtTurn.resize(noOfProcesses);

    wFAllocationTime.resize(noOfProcesses);
    wFDeAllocationTime.resize(noOfProcesses);
    wFAllocatedAtTurn.resize(noOfProcesses);

    mWFAllocationTime.resize(noOfProcesses);
    mWFDeAllocationTime.resize(noOfProcesses);
    mWFAllocatedAtTurn.resize(noOfProcesses);

    //---------------------------------------
    long long int totalBurstTime=0;

    for(long long int i=0;i<noOfProcesses;i++){
        fFBurstTime[i]=rand()%30+1;
        originalBurstTime[i]=fFBurstTime[i];
        wFBurstTime[i]=fFBurstTime[i];
        mWFBurstTime[i]=fFBurstTime[i];
        totalBurstTime+=fFBurstTime[i];

        arrivalTime[i]=rand()%100+20;
        processSize[i]=rand()%(memorySize/4)+20;
        
        fFAllocatedAtTurn[i]=0;
        wFAllocatedAtTurn[i]=0;
        mWFAllocatedAtTurn[i]=0;

        firstFitLoc[i]=NULL;
        worstFitLoc[i]=NULL;
        modifiedWorstFitLoc[i]=NULL;

        //cout<<fFBurstTime[i]<<":";
        //cout<<arrivalTime[i]<<"\n";
    }

    sort(arrivalTime.begin(),arrivalTime.begin()+noOfProcesses);
    arrivalTime[0]=0;

    /*
    for(long long int i=0;i<noOfProcesses;i++){
        cout<<arrivalTime[i]<<":";
        cout<<fFBurstTime[i]<<":";
        cout<<processSize[i]<<" Bytes\n";
    }
    cout<<"\n";
    */

    executeWorstFit();
    executeFirstFit();
    executeModifiedWorstFit();

    cout<<"Total Memory:"<<memorySize<<"\n";
    cout<<"Total Time:"<<totalBurstTime<<"\n";

    /*
    for(long long int i=0;i<noOfProcesses;i++){
        cout<<"Process Id:"<<i<<" Allocated At:"<<allocatedAtTurn[i]<<" Turn Allocation Time:"<<allocationTime[i]<<" Deallocation Time:"<<deAllocationTime[i]<<"\n";;
    }
    */    

    cout<<"\nFirst Fit Total Allocation Time:"<<fFTotalAlloctionTime<<"\n";
    cout<<"\nWorst Fit Total Allocation Time:"<<wFTotalAlloctionTime<<"\n";
    cout<<"\nModified Worst Fit Total Allocation Time:"<<mWFTotalAlloctionTime<<"\n";

    cout<<"\nFirst Fit Total Deallocation Time:"<<fFTotalDeAllocationTime<<"\n";
    cout<<"\nWorst Fit Deallocation Time:"<<wFTotalDeAllocationTime<<"\n";
    cout<<"\nModified Worst Fit Deallocation Time:"<<mWFTotalDeAllocationTime<<"\n";

    executeFirstFit();
    executeWorstFit();
    executeModifiedWorstFit();

    cout<<"Total Memory:"<<memorySize<<"\n";
    cout<<"Total Time:"<<totalBurstTime<<"\n";

    cout<<"\nFirst Fit Total Allocation Time:"<<fFTotalAlloctionTime<<"\n";
    cout<<"\nWorst Fit Total Allocation Time:"<<wFTotalAlloctionTime<<"\n";
    cout<<"\nModified Worst Fit Total Allocation Time:"<<mWFTotalAlloctionTime<<"\n";

    cout<<"\nFirst Fit Total Deallocation Time:"<<fFTotalDeAllocationTime<<"\n";
    cout<<"\nWorst Fit Deallocation Time:"<<wFTotalDeAllocationTime<<"\n";
    cout<<"\nModified Worst Fit Deallocation Time:"<<mWFTotalDeAllocationTime<<"\n";
    
    //-----------------------Excel Sheet Creation-----------------------
    ofstream inFile,fFOutFile,wFOutFile,mWFOutFile,combinedOutFile;

    combinedOutFile.open("Compined_Output_"+fileName+".csv",ios::app);
    combinedOutFile<<"Total Number Of Process:,"<<noOfProcesses<<"\n";
    combinedOutFile<<"Total Main Memory Size:,"<<memorySize<<"\n";
    combinedOutFile<<"Time Quantum for Round Robin:,"<<timeQuantum<<"\n\n";

    combinedOutFile<<"\nFirst Fit Total Allocation Time:,"<<fFTotalAlloctionTime<<endl;
    combinedOutFile<<"\nWorst Fit Total Allocation Time:,"<<wFTotalAlloctionTime<<endl;
    combinedOutFile<<"\nModified Worst Fit Total Allocation Time:,"<<mWFTotalAlloctionTime<<endl;

    combinedOutFile<<"\nFirst Fit Total Deallocation Time:,"<<fFTotalDeAllocationTime<<endl;
    combinedOutFile<<"\nWorst Fit Total Deallocation Time:,"<<wFTotalDeAllocationTime<<endl;
    combinedOutFile<<"\nModified Worst Fit Total Deallocation Time:,"<<mWFTotalDeAllocationTime<<"\n\n";

    combinedOutFile<<"Process Id,Arrival Time,Burst Time,Process Size,First Fit Allocation Turn,First Fit Allocation Time,First Fit Deallocation Time,Worst Fit Allocation Turn,Worst Fit Allocation Time,Worst Fit Deallocation Time,Modified Worst Fit Allocation Turn,Modified Worst Fit Allocation Time,Modified Worst Fit Deallocation Time"<<endl;
    for(int i=0;i<noOfProcesses;i++){
        combinedOutFile<<i<<","<<arrivalTime[i]<<","<<originalBurstTime[i]<<","<<processSize[i]<<","<<fFAllocatedAtTurn[i]<<","<<fFAllocationTime[i]<<","<<fFDeAllocationTime[i]<<","<<wFAllocatedAtTurn[i]<<","<<wFAllocationTime[i]<<","<<wFDeAllocationTime[i]<<","<<mWFAllocatedAtTurn[i]<<","<<mWFAllocationTime[i]<<","<<mWFDeAllocationTime[i]<<endl;
    }

    //Input File
    inFile.open("Input_File_"+fileName+".csv",ios::app);
    inFile<<"Total Number Of Process:,"<<noOfProcesses<<"\n";
    inFile<<"Total Main Memory Size:,"<<memorySize<<"\n";
    inFile<<"Time Quantum for Round Robin:,"<<timeQuantum<<"\n\n";

    inFile<<"\nFirst Fit Total Allocation Time:,"<<fFTotalAlloctionTime<<endl;
    inFile<<"\nWorst Fit Total Allocation Time:,"<<wFTotalAlloctionTime<<endl;
    inFile<<"\nModified Worst Fit Total Allocation Time:,"<<mWFTotalAlloctionTime<<endl;

    inFile<<"\nFirst Fit Total Deallocation Time:,"<<fFTotalDeAllocationTime<<endl;
    inFile<<"\nWorst Fit Total Deallocation Time:,"<<wFTotalDeAllocationTime<<endl;
    inFile<<"\nModified Worst Fit Total Deallocation Time:,"<<mWFTotalDeAllocationTime<<"\n\n";

    inFile<<"Process Id,Arrival Time,Burst Time,Process Size"<<endl;
    for(int i=0;i<noOfProcesses;i++){
        inFile<<i<<","<<arrivalTime[i]<<","<<originalBurstTime[i]<<","<<processSize[i]<<endl;
    }

    //First Fit Output File
    fFOutFile.open("First_Fit_"+fileName+".csv",ios::app);
    fFOutFile<<"Results,of,First,Fit\n\n";
    fFOutFile<<"Process Id,Allocation Turn,Allocation Time,Deallocation Time"<<endl;
    for(int i=0;i<noOfProcesses;i++){
        fFOutFile<<i<<","<<fFAllocatedAtTurn[i]<<","<<fFAllocationTime[i]<<","<<fFDeAllocationTime[i]<<endl;
    }
    
    //Worst Fit Output File
    wFOutFile.open("Worst_Fit_"+fileName+".csv",ios::app);
    wFOutFile<<"Results,of,Worst,Fit\n\n";
    wFOutFile<<"Process Id,Allocation Turn,Allocation Time,Deallocation Time"<<endl;
    for(int i=0;i<noOfProcesses;i++){
        wFOutFile<<i<<","<<wFAllocatedAtTurn[i]<<","<<wFAllocationTime[i]<<","<<wFDeAllocationTime[i]<<endl;
    }

    long long int x1=0,x2=0,x3=0;
    //Modified Worst Fit File
    mWFOutFile.open("Modified_Worst_Fit_"+fileName+".csv",ios::app);
    mWFOutFile<<"Results,of,Modified,Worst,Fit\n\n";
    mWFOutFile<<"Process Id,Allocation Turn,Allocation Time,Deallocation Time"<<endl;
    for(int i=0;i<noOfProcesses;i++){
        mWFOutFile<<i<<","<<mWFAllocatedAtTurn[i]<<","<<mWFAllocationTime[i]<<","<<mWFDeAllocationTime[i]<<endl;
        //printf("%lf,,",mWFAllocationTime[i]);
        x1+=fFAllocationTime[i];
        x2+=wFAllocationTime[i];
        x3+=mWFAllocationTime[i];
    }

    cout<<"\n"<<x1<<"\n"<<x2<<"\n"<<x3;
    return 0;
}