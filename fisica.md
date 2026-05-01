# Dinamica di un urto non elastico e successiva decelerazione
#### Generato da ChatGPT, rivisto e studiato manualmente
In un **urto non elastico**, parte dell’energia cinetica viene dissipata (calore, deformazioni, suono), mentre la **quantità di moto totale si conserva** se il sistema è isolato.

---

# 1. Urto non elastico: fase dell’impatto

## 1.1 Conservazione della quantità di moto

\[
m_1 v_{1i} + m_2 v_{2i} = m_1 v_{1f} + m_2 v_{2f}
\]

### Spiegazione
- \(m_1, m_2\): masse dei due corpi  
- \(v_{1i}, v_{2i}\): velocità prima dell’urto  
- \(v_{1f}, v_{2f}\): velocità dopo l’urto  

👉 Questa equazione dice che la **somma delle quantità di moto prima e dopo l’urto è la stessa**, se non agiscono forze esterne rilevanti.

---

## 1.2 Caso tipico di urto completamente anelastico

Quando i corpi restano attaccati:

\[
v_f = \frac{m_1 v_{1i} + m_2 v_{2i}}{m_1 + m_2}
\]

### Spiegazione
- Dopo l’urto i due corpi hanno **la stessa velocità finale \(v_f\)**  
- L’energia cinetica non si conserva, ma la quantità di moto sì  

👉 Questo è il caso più dissipativo possibile in un urto.

---

## 1.3 Impulso (descrizione dell’urto nel tempo breve)

\[
\vec{J} = \int_{t_i}^{t_f} \vec{F}(t)\, dt = \Delta \vec{p}
\]

### Spiegazione
- \(J\): impulso (effetto complessivo della forza nell’urto)  
- \(F(t)\): forza variabile durante l’impatto  
- \(\Delta p\): variazione della quantità di moto  

👉 L’urto è un evento rapidissimo: invece di seguire la forza istante per istante, si usa il suo effetto totale.

---

## 1.4 Forma semplificata dell’impulso

\[
F_{\text{media}} \Delta t = m (v_f - v_i)
\]

### Spiegazione
- Si sostituisce la forza variabile con una **forza media equivalente**
- \(\Delta t\): durata dell’urto (molto piccola)

👉 Più piccolo è il tempo d’urto, più grande è la forza media.

---

# 2. Dopo l’urto: fase di decelerazione

Dopo l’urto il corpo (o i corpi attaccati) si muove con velocità iniziale \(v_0\) e viene frenato da forze resistive.

---

## 2.1 Seconda legge di Newton

\[
F = m a
\quad \Rightarrow \quad a = \frac{F}{m}
\]

### Spiegazione
- \(F\): forza totale agente sul corpo  
- \(a\): accelerazione (negativa se è una decelerazione)

👉 È la legge fondamentale che lega forza e variazione del moto.

---

## 2.2 Moto con accelerazione costante

### Velocità nel tempo
\[
v = v_0 + a t
\]

#### Spiegazione
- Descrive come cambia la velocità nel tempo  
- Se \(a < 0\), la velocità diminuisce progressivamente

---

### Spostamento nel tempo
\[
x = x_0 + v_0 t + \frac{1}{2} a t^2
\]

#### Spiegazione
- Dà la posizione in funzione del tempo  
- Il termine \(\frac{1}{2} a t^2\) rappresenta l’effetto della decelerazione

---

### Relazione velocità-spazio (senza tempo)
\[
v^2 = v_0^2 + 2 a (x - x_0)
\]

#### Spiegazione
- Utile quando il tempo non è noto  
- Collega direttamente velocità e spazio percorso

👉 È molto usata nei problemi di frenata.

---

## 2.3 Teorema dell’energia cinetica (lavoro delle forze resistive)

\[
W = \Delta K
\]

### Sviluppo nel caso di arresto:

\[
F \cdot d = \frac{1}{2} m v_0^2
\]

### Spiegazione
- \(W\): lavoro della forza frenante  
- \(d\): distanza di arresto  
- \(K = \frac{1}{2} m v^2\): energia cinetica  

👉 Tutta l’energia cinetica iniziale viene dissipata dal lavoro della forza resistente.

---

## 2.4 Forza media di arresto

\[
F = \frac{m v_0^2}{2 d}
\]

### Spiegazione
- Fornisce la **forza media necessaria per fermare il corpo in distanza \(d\)**  
- Più piccola è la distanza di arresto, maggiore è la forza

---

# 3. Collegamento tra urto e decelerazione

1. **Urto non elastico**
   - conserva la quantità di moto
   - riduce l’energia cinetica
   - determina una nuova velocità \(v_0\)

2. **Dopo l’urto**
   - il corpo subisce forze resistive
   - si applica \(F = ma\)
   - il moto segue le equazioni cinematiche o energetiche

---

# Sintesi fisica

- Urto → fenomeno impulsivo (tempo molto breve)
- Decelerazione → fenomeno dinamico continuo
- Strumenti:
  - quantità di moto (urti)
  - Newton + cinematica (frenamento)
  - energia (stima delle forze resistive)