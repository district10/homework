/* GIS Design and Manage Homework
 * @author: Gnat TANG
 * @email: gnat_tang@yeah.net
 * @date: Wed Mar 12, 2014
 */

/* Problem
 * All dollars spent: 50
 * Each man: 5
 * Each woman: 3
 * Each child: 1
 * Then, how many men, women and children?
 */

#include<stdio.h>

int cost(int n_men, int n_women, int n_child);

int main(int argc, char **argv)
{
  int cost_total = 0;
  int cost_each_man = 0;
  int cost_each_woman = 0;
  int cost_each_child = 0;
  if (argc == 5) { /* customize cost of each man, woman, child, and total cost */
    cost_total = atoi(argv[1]);
    cost_each_man = atoi(argv[2]);
    cost_each_woman = atoi(argv[3]);
    cost_each_child = atoi(argv[4]);
  } else if (argc == 1) { /* use built-in configuration */
    cost_total = 50;
    cost_each_man = 5;
    cost_each_woman = 3;
    cost_each_child = 1;
  } else {
    puts("\nWrong Params\nUsage[1]: %s\nUsage[2]: %s <cost_total> <cost_each_man> <cost_each_woman> <cost_each_child>", argv[0], argv[0]);
  }

  int m_a, m_b;
  int w_a, w_b;
  int c_a, c_b;
  m_a = 0, m_b = cost_total / cost_each_man + 1;

}


int cost(int n_men, int n_women, int n_child)
{
  return n_men * cost_each_man + n_women * cost_each_woman + n_child * cost_each_child;
}
