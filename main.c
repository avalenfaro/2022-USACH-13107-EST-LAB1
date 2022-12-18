#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct Parameters
{
  int n;
  int restriction;
};

struct Element
{
  int value;
  int weight;
};

void str_split(char str[], char *split, struct Parameters *p)
{
  int i = 0;
  int restriction;

  char filename[strlen(str) + 1];
  strcpy(filename, str);

  char *piece = strtok(filename, split);
  while (piece != NULL)
  {
    if (i == 1)
    {
      p->n = atoi(piece);
    }

    if (i == 2)
    {
      p->restriction = atoi(piece);
    }

    piece = strtok(NULL, "_");
    i += 1;
  }
}

int bestElementValue = 0;

void binaryBruteForce(int *A, struct Element *elements, int numberOfElements, int i, int restriction)
{
  if (numberOfElements == i)
  {
    int sumValue = 0;
    int sumPond = 0;
    for (int i = 0; i < numberOfElements; i++)
    {
      if (A[i] == 1)
      {
        sumValue += elements[i].value;
        sumPond += elements[i].weight;
      }

      if (sumPond <= restriction)
      {
        if (sumValue > bestElementValue)
        {
          bestElementValue = sumValue;
        }
      }

      printf("%i", A[i]);
    }

    printf(" sumaValores: %d - sumaPonderados: %d\n", sumValue, sumPond);
  }
  else
  {
    A[i] = 0;
    binaryBruteForce(A, elements, numberOfElements, i + 1, restriction);
    A[i] = 1;
    binaryBruteForce(A, elements, numberOfElements, i + 1, restriction);
  }
}

int main(int argc, char *argv[])
{
  struct Parameters parameters;
  int value, weight;
  char str_buffer[30];

  str_split(argv[1], "_", &parameters);

  struct Element *elements = (struct Element *)malloc(sizeof(struct Element) * parameters.n);
  struct Element *results = (struct Element *)malloc((sizeof(struct Element) * parameters.n) * 2);
  int *combinations = (int *)malloc(sizeof(struct Element) * atoi(argv[1]));

  sprintf(str_buffer, "%s/%s", "ejemplos", argv[1]);

  FILE *fp = fopen(str_buffer, "r");

  if (fp == NULL)
  {
    printf("error al abrir el archivo: %s", argv[1]);
    return 0;
  }

  for (int i = 0; i < parameters.n; i++)
  {
    fscanf(fp, "%i %i", &value, &weight);
    elements[i].value = value;
    elements[i].weight = weight;
    printf("%i %i\n", elements[i].value, elements[i].weight);
  }

  binaryBruteForce(combinations, elements, parameters.n, 0, parameters.restriction);

  printf("%d\n", bestElementValue);

  return 0;
}
