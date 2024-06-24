#include "minishell.h"

t_env	*ft_create_node(char *name, char *value)
{
    t_env *new;

    new= malloc(sizeof(t_env));

    if (new)
    {
    new->name=name;
    new->value=value;
    new->next=NULL;
    }
    return (new);
}

void	ft_add_to_list(t_env **head, t_env *newnode)
{
    t_env **node;

    node=head; 
    if (!head || !newnode)
        return;
       
    if (*head)
    {
         head=newnode;
        while (head->next!=NULL)
        {
            head=head->next;
        }
        head->next=newnode;
    }
    else
         *head = node;
}

