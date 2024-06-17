# 1942 - CPP Edition

## Alunos
 - Valdir Rugiski Jr.
 - Wesley Ricardo Lamb

## Controles

Utilize as SETAS DIRECIONAIS para se mover, ESPAÇO para atirar.

## Objetivos

Neutralize a maior quantidade possível de naves inimigas.

## Condições de derrota

Ser atingido ou deixar naves inimigas passarem 3x.

# Documentação

### Enemy: Entity

Classe utilizada para representar uma entidade inimiga.

#### Métodos

##### Enemy(int aX, int aY)
Construtor. Recebe um valor para X e para Y.

##### void render(std::shared_ptr<std::vector\<std::string>> screen)
Desenha o inimigo em screen.

### Engine

A classe Engine é responsável pela maior parte do programa, nela é realizada a atualização dos frames, controle da física e gerencia todas as entidades na tela.

#### Métodos

##### void renderTopBorder(std::shared_ptr<std::vector\<std::string>> screen)
Escreve em screen a parte superior da tela.

##### void renderBottomBorder(std::shared_ptr<std::vector\<std::string>> screen)
Escreve em screen a parte inferior da tela.

##### void renderStatus(std::shared_ptr<std::vector\<std::string>> screen)
Escreve em screen as estatísticas do jogo (pontuação e vidas).

##### void update()
Atualizações físicas das entidades.

##### void render()
Desenha a tela.

##### bool tileInUse(int aX, int aY)
Verifica se certa posição está ocupada.

##### void start()
Inicia o jogo.

##### void addPlayer(Player* aPlayer)
Vincula o jogador à Engine.

##### void playerMove(int xVariation, int yVariation)
Verifica se o jogador pode se mover para uma direção. Se sim, o move.

##### void playerShoot()
Verifica se o jogador pode atirar. Se sim, atira.

#### Atributos

##### Player* player:
Armazena a instância do jogador.

##### int lives = PLAYER_STARTING_LIVES
Quantidade de vidas restantes.

##### int score = 0
Pontuação do jogador.

##### int frame = 0
Contador de frame. Quando chega em 60, reseta.

##### bool canShoot = true
Controla se o jogador pode disparar novamente.

##### bool gameOver = false
Sinaliza se o jogo já acabou.

### Entity

Classe que define todas as entidades desenháveis do jogo.

#### Métodos

##### Entity(int aX, int aY):
Construtor. Recebe os valores de X e Y referentes a posição da entidade.

##### virtual void render(std::shared_ptr<std::vector\<std::string>> screen)
Método abstrato, utilizado para desenhar as entidades.

##### void move(int xVariation, int yVariation)
Aplica um vetor na entidade.

#### Atributos

##### int x
Coordenada X da entidade.

##### int y
Coordenada Y da entidade.

##### int getX()
Encapsulamento de X.

##### int getY()
Encapsulamento de Y.

### Player: Entity

Classe que armazena uma representação do jogador.

#### Métodos

##### Player(int aX, int aY):
Construtor. Recebe um valor para X e para Y.

##### void render(std::shared_ptr<std::vector\<std::string>> screen)
Desenha o jogador em screen.

##### bool isColliding(Entity* anEntity)
Verifica se uma outra entidade está colidindo com o jogador.

### Projectile: Entity

Classe que representa um projétil.

#### Métodos

##### Projectile(int aX, int aY, int aXVariation, int aYVariation)
Construtor. Recebe a posição inicial e um vetor de direção.

##### void render(std::shared_ptr<std::vector\<std::string>> screen)
Desenha o projétil em screen.

##### void move()
Aplica o vetor de dirteção.

#### Atributos

##### int xVariation
Coordenada X do vetor de direção.

##### int yVariation
Coordenada Y do vetor de direção.
