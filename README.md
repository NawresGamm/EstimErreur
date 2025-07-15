# EstimErreur
Résumé des composants et modifications
Ajout d’une fonction Kn générique : gaussian\_noise\_kernel

   * C’est un noyau gaussien corrigé par l’erreur σU
   * Formule :
     Kn(u, σU, h) = 1 / √(2π × variance\_totale) × exp(−½ u² / variance\_totale)
   * Avec :
     variance\_totale = 1 + (σU² / h²)
     Justification : cette correction modélise la présence de bruit sur X

Utilisation de template<typename KernelWithNoise>

   * Permet de passer n’importe quelle fonction Kn(u, σU, h)
   * Évite le coût d’un std::function (appel virtuel)
   * Optimisation : meilleure performance à l’exécution grâce à inlining
