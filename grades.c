/*
  Enock Gansou                   
 */

#include <stdio.h>
#include <math.h>
#define LENGTH 50

/*This function swaps two integers a and b */
static void swap (int  *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/**************************************/
/*   This function find the maxinum   */
/*   between two integers a and b     */
/**************************************/
static int max (int a, int b){
	if (a > b){
		return a;
	}
	
	if (a < b) {
		return b;
	}
	else{
		return a;
	}
}

/*****************************************************************/
/*   This function computes the numeric score using compared     */
/*   grades (weight*score), the actual grades,and the weights    */
/*   put into an array. For a certain of assignments, it drops   */ 
/*   the number of assignments requested                         */
/*****************************************************************/
static double compute_score(int num_assignments, int drop_assignments,
	int compared_grades[], int grades[], int weights [] ){

	int i, j, k ;
	int total_grade = 0, total_weight= 0;
	
  /* Bubble sort actual grades and weights using compared grades */
	for (i = 0; i < num_assignments-1; i++)      
		for (j = 0; j < num_assignments-i-1; j++){ 
			if (compared_grades[j] > compared_grades[j + 1]){
				swap(&compared_grades[j], &compared_grades[j + 1]);
				swap(&grades[j], &grades[j + 1]);
				swap(&weights[j], &weights[j + 1]);
			}
		}
		
  /* Remove k unwanted grades before computing total weight and grade */
		for (k = drop_assignments; k < num_assignments; k++){
			total_grade += grades[k];
			total_weight += weights[k];
		}

		return (double)total_grade / (double)total_weight;
	}


/**************************************************/
/* The program reads assignments and information  */ 
/* about them and  generates the numeric score,   */
/* the mean and the standard deviation            */
/**************************************************/

	int main(){
		
		int drop_assignments, num_assignments, assignment, days_late,
		points_penalty, score, weight, total = 0, total_mean = 0, i, j, k;
		double total_std = 0, mean;
		char stats;
		int grades[LENGTH], compared_grades[LENGTH], weights[LENGTH],
		scores[LENGTH], weights_to_print[LENGTH], days_late_arr[LENGTH];

		scanf("%d  %d %c", &points_penalty, &drop_assignments, &stats);
		
		scanf("%d", &num_assignments);

		for (i = 0; i < num_assignments; i++){

			scanf("%d, %d, %d, %d",&assignment, &score, &weight, &days_late);

    /* To check if total weight is equal to 100 later*/
			total += weight;
			
			total_mean += max(score - days_late * points_penalty, 0);

    /* Arrays used to print the assignments in order */
			scores[assignment - 1] = score;
			weights_to_print[assignment - 1] = weight;
			days_late_arr[assignment - 1] = days_late;

    /* Arrays used to compute the numeric score */
			compared_grades[assignment - 1] = score * weight;
			grades[assignment - 1] = max(score - days_late * points_penalty, 0)
			* weight;
			weights[assignment - 1] = weight;

		}
		
  /* Whether the total weight is equal to 100 */
		if (total != 100){
			printf("ERROR:Invalid values provided\n");
		}

		else {
    /* Print general information */
			printf("Numeric score: %5.4f\n", compute_score(num_assignments,
				drop_assignments, compared_grades, grades, weights ));
			printf("Points Penalty Per Day Late: %d\n", points_penalty);
			printf("Number of Assignments Dropped: %d\n", drop_assignments);
			printf("Values provided:\n");
			printf("Assignment, Score, Weight, Days Late\n");

    /* Print assignments information */
			for (j = 0; j < num_assignments; j++ ){
				printf("%d, %d, %d, %d\n",j + 1, scores[j], weights_to_print[j],
					days_late_arr[j]);
			}
			
    /* Print the mean and the standard deviation */
			if(stats=='y'||stats=='Y'){
				mean=(double)total_mean / (double)num_assignments;
				
				for(k = 0; k < num_assignments; k++){
					total_std += pow((double)max(scores[k] - days_late_arr[k] *
						points_penalty, 0) - mean, 2.0);
				}
				
				printf("Mean: %5.4f, Standard Deviation: %5.4f\n",
					mean,sqrt(total_std / (double)num_assignments));
			}
			
		}

		return 0;
		
	}



