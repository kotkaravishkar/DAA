#include<bits/stdc++.h>
using namespace std;

double fractionalKnapsack(int W, int n, vector<int>&  weights, vector<int>& values);
int boundedKnapsack(int W, int n, vector<int>&  weights, vector<int>& values);
void whichIsBetter(int W, int n, vector<int>&  weights, vector<int>& values);

int main() {

    int option = 1;
    while(option) {
        
        int W;
        cout << "Enter capacity of the Knapsack: ";
        cin >> W;

        int n;
        cout << "Enter number of items: ";
        cin >> n;
        
        vector<int> weights;
        cout << "Enter weights of n items: ";
        for(int i=0; i<n; i++) {
            int wt;
            cin >> wt;
            weights.push_back(wt);
        }

        vector<int> values;
        cout << "Enter price of n items: ";
        for(int i=0; i<n; i++) {
            int price;
            cin >> price;
            values.push_back(price);
        }    

        cout << "1. Fractional Knapsack   2. 0/1 Knapsack   3. Both (comparison)   0. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        switch (option) {
            case 1: fractionalKnapsack(W, n, weights, values);
                    break;
            case 2: boundedKnapsack(W, n, weights, values);
                    break;
            case 3: whichIsBetter(W, n, weights, values);
                    break;
            case 0: cout << "\n----- Thank you! ----";
                    break;
            default: cout << "Invalid choice!\n";
                    break;
        }
    }
    return 0;
}

double fractionalKnapsack(int W, int n, vector<int>&  weights, vector<int>& values) {
    vector< pair <double, int> > pricePerKg;  
    for(int i=0; i<n; i++) {
        double average = values[i]/(double)weights[i];
        pricePerKg.push_back(make_pair(average, i));
    }
    sort(pricePerKg.begin(), pricePerKg.end());
    double profit = 0;
    double capacity = 0;
    for(int i=n-1; i>=0; i--) {
        int index = pricePerKg[i].second;
        double p = pricePerKg[i].first;
        if(capacity == W) {
            break;
        }
        if(W >= capacity+weights[index]) {
            profit += values[index];
            capacity += weights[index];
        }
        else {
            double total_wt = 0;
            while(capacity+1 <= W) {
                capacity += 1;
                total_wt += 1;
                profit += p;
                if(total_wt == weights[index]) {
                    break;
                }
            }
            break;
        }
    }
    cout << profit << endl;
    return profit;
}
int boundedKnapsack(int W, int n, vector<int>&  weights, vector<int>& values) {
    int dp[n+1][W+1];
	memset(dp, -1, sizeof(dp));
	for(int i=0; i<=n; i++) {
		for(int j=0; j<=W; j++) {
			if(i*j == 0) {
				dp[i][j] = 0;
			} 
		}
	}
	for(int i=1; i<=n; i++) {
		for(int j=1; j<=W; j++) {
			if(weights[i-1] <= j) {
				dp[i][j] = max(values[i-1]+dp[i-1][j-weights[i-1]], dp[i-1][j]);
			} 
			else {
				dp[i][j] = dp[i-1][j];
			}
		}
	}
    cout << dp[n][W] << endl;
	return dp[n][W];
}
void whichIsBetter(int W, int n, vector<int>&  weights, vector<int>& values) {
    int a = boundedKnapsack(W, n, weights, values);
    double b = fractionalKnapsack(W, n, weights, values);
    if(a == b) {
        cout << "SAME RESULTS\n";
    }
    else if(a> b) {
        cout << "0/1knapsack is better\n";
    }
    else {
        cout << "fractional knapsack is better\n";
    }
}