#include <stdio.h>  // Standard input/output functions
#include <string.h> // String handling functions

// ----------------- HOSPITAL STRUCTURE -----------------
struct Hospital
{
int id;       // Hospital ID
char name[30]; // Hospital name
char city[20]; // City where hospital is located
int beds;      // Number of available beds
float price;   // Bed price per day
float rating;  // Hospital rating (0–5)
int reviews;   // Number of reviews
};

// ----------------- PATIENT STRUCTURE -----------------
struct Patient
{
int id;             // Patient ID
char name[30];      // Patient name
int age;            // Patient age
char disease[30];   // Disease or condition
int hospitalID;     // ID of hospital where patient is admitted
};

int main()
{
    int choice;         // Stores menu choice
    struct Hospital h;  // Hospital structure variable
    struct Patient p;   // Patient structure variable
    FILE *fp;           // File pointer

    // Menu loop (runs until user chooses exit)
    do
    {
        printf("\n===== HOSPITAL MANAGEMENT SYSTEM ====="); // Main heading
        printf("\n1. Add Hospital");                       // Menu option 1
        printf("\n2. Show Hospitals");                    // Menu option 2
        printf("\n3. Add Patient");                       // Menu option 3
        printf("\n4. Show Patients");                     // Menu option 4
        printf("\n5. Sort Hospitals by Bed Price (High to Low)"); // Menu option 5
        printf("\n0. Exit");                               // Exit option
        printf("\nEnter choice: ");                        // Ask user choice
        scanf("%d", &choice);                              // Read choice
        getchar();                                         // Clear input buffer

        // ----------------- ADD HOSPITAL -----------------
        if (choice == 1)
        {
            fp = fopen("hospital.dat", "ab"); // Open hospital file in append mode
            if (fp == NULL)                   // Check file error
            {
                printf("File error\n");       // Show error
                continue;                     // Skip loop iteration
            }

            printf("Enter Hospital ID: ");    // Ask hospital ID
            scanf("%d", &h.id);               // Read ID
            getchar();                        // Clear buffer

            printf("Enter Hospital Name: ");  // Ask hospital name
            fgets(h.name, sizeof(h.name), stdin); // Read name
            h.name[strcspn(h.name, "\n")] = '\0'; // Remove newline

            printf("Enter City: ");           // Ask city
            fgets(h.city, sizeof(h.city), stdin); // Read city
            h.city[strcspn(h.city, "\n")] = '\0'; // Remove newline

            printf("Enter Available Beds: "); // Ask available beds
            scanf("%d", &h.beds);             // Read beds

            printf("Enter Bed Price: ");      // Ask bed price
            scanf("%f", &h.price);            // Read price

            printf("Enter Hospital Rating (0-5): "); // Ask rating
            scanf("%f", &h.rating);           // Read rating

            printf("Enter Number of Reviews: "); // Ask reviews count
            scanf("%d", &h.reviews);           // Read reviews

            fwrite(&h, sizeof(h), 1, fp);      // Write hospital to file
            fclose(fp);                        // Close file

            printf("Hospital added successfully!\n"); // Success message
        }

        // ----------------- SHOW HOSPITAL -----------------
        else if (choice == 2)
        {
            fp = fopen("hospital.dat", "rb"); // Open file in read mode
            if (fp == NULL)                   // If file not found
            {
                printf("No hospital data found\n"); // Message
                continue;
            }

            printf("\n--- HOSPITAL LIST ---\n"); // Heading
            while (fread(&h, sizeof(h), 1, fp)) // Read records
            {
                printf("\nID: %d", h.id);      // Print ID
                printf("\nName: %s", h.name);  // Print name
                printf("\nCity: %s", h.city);  // Print city
                printf("\nBeds: %d", h.beds);  // Print beds
                printf("\nPrice: %.2f", h.price); // Print price
                printf("\nRating: %.1f", h.rating); // Print rating
                printf("\nReviews: %d\n", h.reviews); // Print reviews
            }
            fclose(fp);                        // Close file
        }

        // ----------------- ADD PATIENT -----------------
        else if (choice == 3)
        {
            fp = fopen("patient.dat", "ab");   // Open patient file
            if (fp == NULL)                    // Check error
            {
                printf("File error\n");
                continue;
            }

            printf("Enter Patient ID: ");      // Ask patient ID
            scanf("%d", &p.id);                // Read ID
            getchar();

            printf("Enter Patient Name: ");    // Ask name
            fgets(p.name, sizeof(p.name), stdin);
            p.name[strcspn(p.name, "\n")] = '\0';

            printf("Enter Age: ");              // Ask age
            scanf("%d", &p.age);
            getchar();

            printf("Enter Disease/Condition: "); // Ask disease
            fgets(p.disease, sizeof(p.disease), stdin);
            p.disease[strcspn(p.disease, "\n")] = '\0';

            printf("Enter Hospital ID (where admitted): "); // Ask hospital ID
            scanf("%d", &p.hospitalID);

            fwrite(&p, sizeof(p), 1, fp);       // Write patient data
            fclose(fp);                         // Close file

            printf("Patient added successfully!\n");
        }

        // ----------------- SHOW PATIENT -----------------
        else if (choice == 4)
        {
            FILE *hospFile;                     // File pointer for hospital
            fp = fopen("patient.dat", "rb");    // Open patient file
            if (fp == NULL)
            {
                printf("No patient data found\n");
                continue;
            }

            printf("\n--- PATIENT LIST ---\n");
            while (fread(&p, sizeof(p), 1, fp))
            {
                printf("\nPatient ID: %d", p.id);
                printf("\nName: %s", p.name);
                printf("\nAge: %d", p.age);
                printf("\nDisease: %s", p.disease);
                printf("\nHospital ID: %d", p.hospitalID);

                hospFile = fopen("hospital.dat", "rb"); // Open hospital file
                if (hospFile != NULL)
                {
                    while (fread(&h, sizeof(h), 1, hospFile))
                    {
                        if (h.id == p.hospitalID) // Match hospital ID
                        {
                            printf("\nHospital Name: %s", h.name);
                            break;
                        }
                    }
                    fclose(hospFile);
                }
                printf("\n");
            }
            fclose(fp);
        }

        // ----------------- SORT HOSPITALS BY BED PRICE -----------------
        else if (choice == 5)
        {
            struct Hospital hospitals[100]; // Array to store hospitals
            int count = 0, i, j;             // Counters
            fp = fopen("hospital.dat", "rb");
            if (fp == NULL)
            {
                printf("No hospital data found\n");
                continue;
            }

            while (fread(&h, sizeof(h), 1, fp))
            {
                hospitals[count++] = h;      // Store data in array
            }
            fclose(fp);

            struct Hospital temp;             // Temporary variable
            for (i = 0; i < count - 1; i++)
            {
                for (j = 0; j < count - i - 1; j++)
                {
                    if (hospitals[j].price < hospitals[j + 1].price)
                    {
                        temp = hospitals[j];
                        hospitals[j] = hospitals[j + 1];
                        hospitals[j + 1] = temp;
                    }
                }
            }

            printf("\n--- HOSPITALS SORTED BY BED PRICE (HIGH TO LOW) ---\n");
            for (i = 0; i < count; i++)
            {
                printf("\nID: %d", hospitals[i].id);
                printf("\nName: %s", hospitals[i].name);
                printf("\nCity: %s", hospitals[i].city);
                printf("\nBeds: %d", hospitals[i].beds);
                printf("\nPrice: %.2f", hospitals[i].price);
                printf("\nRating: %.1f", hospitals[i].rating);
                printf("\nReviews: %d\n", hospitals[i].reviews);
            }
        }
        else{
            printf("INVALID CHOICE");
        }

    } while (choice != 0); // Loop until exit chosen

    printf("\nExiting program...\n"); // Exit message
    return 0;                         // End program
}
